#include "modul-signal-extractor.h"

/* Modulmethoden / Implementierungen: Beginn                                  */

uint8_t extractor_init(signal_extractor* ext)
{
  ext->state = STATE_IDLE;
  ext->start_time = 0;
  ext->current_time = 0;
  ext->last_pin_value = 0;
  ext->symbol_count = 0;
  ext->word_complete = 0;
  return 0;
}

uint8_t extractor_process_sample(signal_extractor* ext, uint8_t pin_value)
{
  uint8_t char_complete = 0;
  uint8_t duration;
  uint8_t pause;
  
  // Zeit aktualisieren
  ext->current_time++;
  
  // Flanken-Erkennung
  if (pin_value != ext->last_pin_value)
  {
    // LOW→HIGH Flanke
    if (pin_value == 1)
    {
      // Starte neue HIGH-Phase
      ext->start_time = ext->current_time;
      ext->state = STATE_SIGNAL_HIGH;
    }
    // HIGH→LOW Flanke
    else
    {
      if (ext->state == STATE_SIGNAL_HIGH)
      {
        // Messe vorheriges HIGH-Signal
        duration = ext->current_time - ext->start_time;
        
        // Klassifiziere als DIT oder DAH
        if (duration >= 1 && duration < TIMING_DIT_MAX)
        {
          // DIT erkannt
          if (ext->symbol_count < 8)
          {
            ext->symbols[ext->symbol_count] = MORSE_DIT;
            ext->symbol_count++;
          }
        }
        else if (duration >= TIMING_DAH_MIN && duration < TIMING_DAH_MAX)
        {
          // DAH erkannt
          if (ext->symbol_count < 8)
          {
            ext->symbols[ext->symbol_count] = MORSE_DAH;
            ext->symbol_count++;
          }
        }
        else
        {
          // Ungültige Dauer - Reset
          ext->symbol_count = 0;
          ext->state = STATE_IDLE;
          ext->last_pin_value = pin_value;
          return 0;
        }
      }
      
      // Starte Pause-Messung
      ext->start_time = ext->current_time;
      ext->state = STATE_SIGNAL_LOW;
    }
  }
  // Keine Flanke
  else
  {
    if (ext->state == STATE_SIGNAL_LOW || ext->state == STATE_CHAR_COMPLETE)
    {
      // Messe Pause-Dauer
      pause = ext->current_time - ext->start_time;
      
      // Prüfe auf Zeichen-Ende
      if (pause >= TIMING_CHAR_SPACE)
      {
        // Prüfe ob Symbole vorhanden
        if (ext->symbol_count > 0)
        {
          // Prüfe auf Wort-Ende
          if (pause >= TIMING_WORD_SPACE)
          {
            ext->word_complete = 1;
          }
          else
          {
            ext->word_complete = 0;
          }
          
          ext->state = STATE_CHAR_COMPLETE;
          char_complete = 1;
        }
      }
    }
  }
  
  // Letzten Wert speichern
  ext->last_pin_value = pin_value;
  
  return char_complete;
}

uint8_t extractor_get_symbols(signal_extractor* ext, MorseSymbol* output_symbols)
{
  // Kopiere Symbole
  for (uint8_t i = 0; i < ext->symbol_count; i++)
  {
    output_symbols[i] = ext->symbols[i];
  }
  
  return ext->symbol_count;
}

uint8_t extractor_is_word_complete(signal_extractor* ext)
{
  return ext->word_complete;
}

void extractor_reset(signal_extractor* ext)
{
  ext->state = STATE_IDLE;
  ext->start_time = 0;
  ext->symbol_count = 0;
  ext->word_complete = 0;
}

/* Modulmethoden / Implementierungen: Ende                                    */
// EOF
