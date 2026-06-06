/*!
  \file test-uart-1a.c
  \brief Test Übung 1a - Kontinuierliches Senden der Teamnummer
*/

#include "modul-uart-hardware.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

int main(void)
{
  /* Initialisiere UART */
  modul_uart_init();
  
  /* Aktiviere Interrupts */
  sei();
  
  /* Hauptschleife */
  while(1)
  {
    /* Sende Teamnummer */
    uart_send_string("Team 24\r\n");
    
    /* Warte 1 Sekunde */
    _delay_ms(1000);
  }
  
  return 0;
}
