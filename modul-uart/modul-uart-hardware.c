#include "modul-uart-hardware.h"
#include <avr/io.h>
#include <avr/interrupt.h>

/* Hardware-spezifische Implementierung: Beginn                               */

/* Globale Buffer */
static uart_tx_buffer tx_buffer;
static uart_rx_buffer rx_buffer;

uint8_t modul_uart_init(void)
{
  /* Initialisiere Buffer */
  uart_tx_init(&tx_buffer);
  uart_rx_init(&rx_buffer);
  
  /* Berechne UBRR für 9600 Baud bei 16 MHz */
  /* UBRR = (F_CPU / (16 * BAUD)) - 1 */
  /* UBRR = (16000000 / (16 * 9600)) - 1 = 103.17 ≈ 103 */
  uint16_t ubrr = 103;
  
  /* Setze Baud Rate */
  UBRR0H = (uint8_t)(ubrr >> 8);
  UBRR0L = (uint8_t)ubrr;
  
  /* Konfiguriere USART0:
   * - Asynchronous Mode
   * - Ungerade Parität (ODD) - UPM01=1, UPM00=1
   * - 2 Stop Bits - USBS0=1
   * - 8 Data Bits - UCSZ01=1, UCSZ00=1
   */
  UCSR0C = (1 << UPM01) | (1 << UPM00) |  /* Odd Parity */
           (1 << USBS0) |                  /* 2 Stop Bits */
           (1 << UCSZ01) | (1 << UCSZ00);  /* 8 Data Bits */
  
  /* Enable RX, TX und RX Complete Interrupt */
  UCSR0B = (1 << RXEN0) |   /* RX Enable */
           (1 << TXEN0) |   /* TX Enable */
           (1 << RXCIE0);   /* RX Complete Interrupt Enable */
  /* TX Interrupt wird erst aktiviert wenn Daten zu senden sind */
  
  return 0;
}

uint8_t modul_uart_run(void)
{
  /* Logik ist in den ISRs */
  return 0;
}

uint8_t uart_send_byte(uint8_t data)
{
  /* Füge Byte in TX-Buffer ein */
  uint8_t result = uart_tx_put(&tx_buffer, data);
  
  if (result == 0)
  {
    /* Aktiviere TX Data Register Empty Interrupt */
    UCSR0B |= (1 << UDRIE0);
  }
  
  return result;
}

uint8_t uart_send_string(const char* str)
{
  while (*str)
  {
    uint8_t result = uart_send_byte(*str);
    if (result != 0)
    {
      return result; /* Buffer voll */
    }
    str++;
  }
  return 0;
}

uint8_t uart_receive_byte(uint8_t* data)
{
  return uart_rx_get(&rx_buffer, data);
}

uint8_t uart_available(void)
{
  return uart_rx_count(&rx_buffer);
}

/* USART RX Complete Interrupt */
ISR(USART0_RX_vect)
{
  /* Lese empfangenes Byte */
  uint8_t data = UDR0;
  
  /* Füge in RX-Buffer ein */
  uart_rx_put(&rx_buffer, data);
}

/* USART Data Register Empty Interrupt */
ISR(USART0_UDRE_vect)
{
  uint8_t data;
  
  /* Hole Byte aus TX-Buffer */
  if (uart_tx_get(&tx_buffer, &data) == 0)
  {
    /* Sende Byte */
    UDR0 = data;
  }
  else
  {
    /* TX-Buffer leer, deaktiviere Interrupt */
    UCSR0B &= ~(1 << UDRIE0);
  }
}

/* Hardware-spezifische Implementierung: Ende                                 */
// EOF
