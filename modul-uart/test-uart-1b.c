/*!
  \file test-uart-1b.c
  \brief Test Übung 1b - Senden nur wenn Ziffer empfangen
*/

#include "modul-uart-hardware.h"
#include <avr/io.h>
#include <avr/interrupt.h>

int main(void)
{
  /* Initialisiere UART */
  modul_uart_init();
  
  /* Aktiviere Interrupts */
  sei();
  
  /* Hauptschleife */
  while(1)
  {
    uint8_t data;
    
    /* Prüfe ob Byte empfangen */
    if (uart_receive_byte(&data) == 0)
    {
      /* Prüfe ob es eine Ziffer ist (0-9) */
      if (data >= '0' && data <= '9')
      {
        /* Sende Teamnummer */
        uart_send_string("Team 24\r\n");
      }
    }
  }
  
  return 0;
}
