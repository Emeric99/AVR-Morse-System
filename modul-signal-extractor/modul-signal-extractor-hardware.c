#include "modul-signal-extractor-hardware.h"
#include <avr/io.h>
#include <avr/interrupt.h>

/* Hardware-spezifische Implementierung: Beginn                               */

/* Globale Extractor-Instanz */
static signal_extractor extractor;

/* LED-Feedback State */
static uint8_t led_counter = 0;

uint8_t modul_signal_extractor_init(void)
{
  /* Initialisiere Extractor */
 extractor_init(&extractor);
  
  /* PINC.1 als Eingang für Morse-Signal (VCD nutzt Pin 1!) */
  DDRC &= ~(1 << DDC1);
  PORTC &= ~(1 << PORTC1);
  
  /* PORTD.0 als Ausgang für LED-Feedback */
  DDRD |= (1 << DDD0);
  PORTD &= ~(1 << PORTD0);
  
  /* Timer konfigurieren (1000Hz = 1ms Interrupt für VCD compatibility) */
  /* Timer1 CTC Mode */
  TCCR1A = 0;
  TCCR1B = (1 << WGM12) | (1 << CS11) | (1 << CS10);  /* CTC, Prescaler 64 */
  OCR1A = 249;  /* 16MHz / 64 / 1000Hz - 1 = 249 */
  TIMSK1 = (1 << OCIE1A);  /* Enable Timer1 Compare Interrupt */
  
  return 0;
}

uint8_t modul_signal_extractor_run(void)
{
  /* Wird nicht verwendet - Logik ist im ISR */
  return 0;
}

/* Getter-Funktionen für andere Module */
uint8_t signal_extractor_get_last_symbols(MorseSymbol* symbols)
{
  return extractor_get_symbols(&extractor, symbols);
}

uint8_t signal_extractor_is_word_complete_hw(void)
{
  return extractor_is_word_complete(&extractor);
}

void signal_extractor_reset_hw(void)
{
  extractor_reset(&extractor);
}

/* Timer1 Compare Interrupt - wird alle 1ms aufgerufen */
ISR(TIMER1_COMPA_vect)
{
  /* Lese Morse-Signal Pin  */
  uint8_t pin_value = (PINC & (1 << PINC1)) ? 1 : 0;
  
  /* Verarbeite Sample */
  uint8_t char_complete = extractor_process_sample(&extractor, pin_value);
  
  if (char_complete)
  {
    /* LED einschalten für Feedback */
    PORTD |= (1 << PORTD0);
    led_counter = 500;  /* LED für 500ms an (500 * 1ms) */
  }
  
  /* LED-Timeout */
  if (led_counter > 0)
  {
    led_counter--;
    if (led_counter == 0)
    {
      PORTD &= ~(1 << PORTD0);  /* LED aus */
    }
  }
}

/* Hardware-spezifische Implementierung: Ende                                 */
// EOF
