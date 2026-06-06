#include "modul-morse-generator-hardware.h"
#include <avr/io.h>
#include <avr/interrupt.h>

/* Hardware-spezifische Implementierung: Beginn                               */

/* Globale Generator-Instanz */
morse_generator morse_gen;

uint8_t modul_morse_generator_init(void)
{
  /* Initialisiere Generator */
  generator_init(&morse_gen);
  
  /* PORTC.2 als Ausgang für Morse-Signal */
  DDRC |= (1 << DDC2);
  PORTC &= ~(1 << PORTC2);  /* Signal LOW */
  
  /* Timer2 konfigurieren (1000Hz = 1ms Interrupt) */
  /* Timer2 CTC Mode */
  TCCR2A = (1 << WGM21);  /* CTC Mode */
  TCCR2B = (1 << CS22) | (1 << CS21) | (1 << CS20);  /* Prescaler 1024 */
  OCR2A = 15;  /* 16MHz / 1024 / 1000Hz - 1 ≈ 15 */
  TIMSK2 = (1 << OCIE2A);  /* Enable Timer2 Compare Interrupt */
  
  return 0;
}

uint8_t modul_morse_generator_run(void)
{
  /* Logik ist im ISR */
  return 0;
}

/* Wrapper-Funktionen für andere Module */
uint8_t morse_generator_send_symbols_hw(const MorseSymbol* symbols, uint8_t count)
{
  return generator_send_symbols(&morse_gen, symbols, count);
}

uint8_t morse_generator_send_space_hw(void)
{
  return generator_send_space(&morse_gen);
}

uint8_t morse_generator_is_busy_hw(void)
{
  return generator_is_busy(&morse_gen);
}

/* Timer2 Compare Interrupt - wird alle 1ms aufgerufen */
ISR(TIMER2_COMPA_vect)
{
  /* Verarbeite Tick */
  uint8_t pin_value = generator_process_tick(&morse_gen);
  
  /* Setze Output-Pin entsprechend */
  if (pin_value)
  {
    PORTC |= (1 << PORTC2);   /* Pin HIGH */
  }
  else
  {
    PORTC &= ~(1 << PORTC2);  /* Pin LOW */
  }
}

/* Hardware-spezifische Implementierung: Ende                                 */
// EOF
