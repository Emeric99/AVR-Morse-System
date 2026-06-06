/*!
  \file test-uart-1c.c
  \brief Test Übung 1c - Start/Stop mit Tastern
*/

#include "modul-uart-hardware.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

/* Globale Variable für Sende-Status */
 uint8_t sending_active = 0;

/* Button Debouncing */
uint8_t button_pressed(uint8_t button_pin)
{
  static uint8_t button_state = 0;
  static uint8_t last_button_state = 0;
  
  button_state = (PINA & (1 << button_pin)) ? 0 : 1; /* Active low */
  
  if (button_state && !last_button_state)
  {
    last_button_state = button_state;
    _delay_ms(50); /* Debounce */
    return 1;
  }
  
  last_button_state = button_state;
  return 0;
}

int main(void)
{
  /* Initialisiere UART */
  modul_uart_init();
  
  /* Konfiguriere Taster als Eingänge mit Pull-Up */
  DDRA &= ~((1 << PA0) | (1 << PA1)); /* PA0 = Taster1, PA1 = Taster2 */
  PORTA |= (1 << PA0) | (1 << PA1);   /* Pull-Up aktivieren */
  
  /* Aktiviere Interrupts */
  sei();
  
  /* Hauptschleife */
  while(1)
  {
    /* Prüfe Taster 1 (Start) */
    if (button_pressed(0))
    {
      sending_active = 1;
      uart_send_string("START\r\n");
    }
    
    /* Prüfe Taster 2 (Stop) */
    if (button_pressed(1))
    {
      sending_active = 0;
      uart_send_string("STOP\r\n");
    }
    
    /* Sende wenn aktiv */
    if (sending_active)
    {
      uart_send_string("Team 24\r\n");
      _delay_ms(1000);
    }
  }
  
  return 0;
}
