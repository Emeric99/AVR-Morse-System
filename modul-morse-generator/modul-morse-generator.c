#include "modul-morse-generator.h"

/* Modulmethoden / Implementierungen: Beginn                                  */

uint8_t generator_init(morse_generator* gen)
{
  gen->state = GEN_STATE_IDLE;
  gen->symbol_count = 0;
  gen->current_symbol = 0;
  gen->tick_counter = 0;
  gen->target_ticks = 0;
  gen->is_busy = 0;
  return 0;
}

uint8_t generator_send_symbols(morse_generator* gen, const MorseSymbol* symbols, uint8_t count)
{
  // Prüfe ob Generator beschäftigt
  if (gen->is_busy)
  {
    return 1; // Fehler: noch beschäftigt
  }
  
  // Kopiere Symbole
  if (count > 8)
  {
    count = 8; // Maximal 8 Symbole
  }
  
  for (uint8_t i = 0; i < count; i++)
  {
    gen->symbols[i] = symbols[i];
  }
  
  gen->symbol_count = count;
  gen->current_symbol = 0;
  gen->tick_counter = 0;
  gen->is_busy = 1;
  
  // Starte mit erstem Symbol
  if (count > 0)
  {
    gen->state = GEN_STATE_SENDING_SYMBOL;
    
    // Setze Dauer basierend auf Symbol-Typ
    if (gen->symbols[0] == MORSE_DIT)
    {
      gen->target_ticks = TIMING_DIT_DURATION;
    }
    else
    {
      gen->target_ticks = TIMING_DAH_DURATION;
    }
  }
  
  return 0; // Erfolg
}

uint8_t generator_send_space(morse_generator* gen)
{
  // Prüfe ob Generator beschäftigt
  if (gen->is_busy)
  {
    return 1; // Fehler: noch beschäftigt
  }
  
  // Sende nur Pause
  gen->symbol_count = 0;
  gen->current_symbol = 0;
  gen->tick_counter = 0;
  gen->target_ticks = TIMING_WORD_PAUSE;
  gen->state = GEN_STATE_PAUSE_CHAR;
  gen->is_busy = 1;
  
  return 0; // Erfolg
}

uint8_t generator_process_tick(morse_generator* gen)
{
  uint8_t pin_value = 0;
  
  // Wenn IDLE, nichts zu tun
  if (gen->state == GEN_STATE_IDLE)
  {
    return 0;
  }
  
  // State Machine
  switch (gen->state)
  {
    case GEN_STATE_SENDING_SYMBOL:
      // Pin HIGH während Symbol gesendet wird
      pin_value = 1;
      
      // Inkrementiere Tick-Counter
      gen->tick_counter++;
      
      // Prüfe ob Symbol fertig
      if (gen->tick_counter >= gen->target_ticks)
      {
        gen->tick_counter = 0;
        gen->current_symbol++;
        
        // Prüfe ob mehr Symbole
        if (gen->current_symbol < gen->symbol_count)
        {
          // Pause zwischen Symbolen
          gen->state = GEN_STATE_PAUSE_INTRA;
          gen->target_ticks = TIMING_INTRA_PAUSE;
        }
        else
        {
          // Alle Symbole gesendet, Zeichen-Pause
          gen->state = GEN_STATE_PAUSE_CHAR;
          gen->target_ticks = TIMING_CHAR_PAUSE;
        }
      }
      break;
      
    case GEN_STATE_PAUSE_INTRA:
      // Pin LOW während Pause
      pin_value = 0;
      
      // Inkrementiere Tick-Counter
      gen->tick_counter++;
      
      // Prüfe ob Pause fertig
      if (gen->tick_counter >= gen->target_ticks)
      {
        gen->tick_counter = 0;
        
        // Sende nächstes Symbol
        gen->state = GEN_STATE_SENDING_SYMBOL;
        
        if (gen->symbols[gen->current_symbol] == MORSE_DIT)
        {
          gen->target_ticks = TIMING_DIT_DURATION;
        }
        else
        {
          gen->target_ticks = TIMING_DAH_DURATION;
        }
      }
      break;
      
    case GEN_STATE_PAUSE_CHAR:
      // Pin LOW während Zeichen-Pause
      pin_value = 0;
      
      // Inkrementiere Tick-Counter
      gen->tick_counter++;
      
      // Prüfe ob Pause fertig
      if (gen->tick_counter >= gen->target_ticks)
      {
        gen->tick_counter = 0;
        gen->state = GEN_STATE_IDLE;
        gen->is_busy = 0;
      }
      break;
      
    default:
      pin_value = 0;
      break;
  }
  
  return pin_value;
}

uint8_t generator_is_busy(morse_generator* gen)
{
  return gen->is_busy;
}

void generator_stop(morse_generator* gen)
{
  gen->state = GEN_STATE_IDLE;
  gen->is_busy = 0;
  gen->tick_counter = 0;
  gen->symbol_count = 0;
}

/* Modulmethoden / Implementierungen: Ende                                    */
// EOF
