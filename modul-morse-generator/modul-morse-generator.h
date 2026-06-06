/*!
  \file modul-morse-generator.h
  \brief Hardware-unabhängige Definitionen für Morse-Generator
 
  \details Generiert Morse-Signal-Timing aus Symbolen (DIT/DAH)

  \author Emeric Tcholagheu
  \author Joyce Sonkwe
*/

#ifndef _MODUL_MORSE_GENERATOR_H
#define _MODUL_MORSE_GENERATOR_H 1

/* Importe: Beginn                                                            */
#include <inttypes.h>
#include "../morse-types.h"
/* Importe: Ende                                                              */

/*----------------------------------------------------------------------------*/
/* Datenstrukturen: Beginn                                                    */

/*!
  \brief Morse-Symbol Typ
*/

/*!
  \brief Generator State Machine
*/
typedef enum {
  GEN_STATE_IDLE = 0,           // Wartet auf Symbole
  GEN_STATE_SENDING_SYMBOL = 1, // Sendet Symbol (Pin HIGH)
  GEN_STATE_PAUSE_INTRA = 2,    // Pause zwischen Symbolen
  GEN_STATE_PAUSE_CHAR = 3      // Pause zwischen Zeichen
} GeneratorState;

/*!
  \brief Timing-Konstanten (bei 1ms = 1 Tick)
*/
typedef enum {
  TIMING_DIT_DURATION = 1,    // 1 Tick = 1ms
  TIMING_DAH_DURATION = 3,    // 3 Ticks = 3ms
  TIMING_INTRA_PAUSE = 1,     // 1 Tick = 1ms (zwischen Symbolen)
  TIMING_CHAR_PAUSE = 3,      // 3 Ticks = 3ms (zwischen Zeichen)
  TIMING_WORD_PAUSE = 7       // 7 Ticks = 7ms (zwischen Wörtern)
} GeneratorTiming;

/*!
  \brief Generator Status
*/
typedef struct morse_generator
{
  uint8_t state;              // State Machine
  MorseSymbol symbols[8];     // Symbole zum Senden
  uint8_t symbol_count;       // Anzahl Symbole
  uint8_t current_symbol;     // Aktuelles Symbol-Index
  uint8_t tick_counter;       // Tick-Counter für Timing
  uint8_t target_ticks;       // Ziel-Ticks für aktuellen State
  uint8_t is_busy;            // 1 wenn Generator beschäftigt
} morse_generator;

/* Datenstrukturen: Ende                                                      */
/*----------------------------------------------------------------------------*/
/* Modulmethoden / Definitionen: Beginn                                       */

/*!
  \brief Initialisiert den Generator
  
  \param gen Zeiger auf Generator-Struktur
  \return 0 bei Erfolg
*/
uint8_t generator_init(morse_generator* gen);

/*!
  \brief Startet das Senden von Symbolen
  
  \param gen Zeiger auf Generator-Struktur
  \param symbols Array von Symbolen zum Senden
  \param count Anzahl Symbole
  \return 0 bei Erfolg, 1 wenn Generator beschäftigt
*/
uint8_t generator_send_symbols(morse_generator* gen, const MorseSymbol* symbols, uint8_t count);

/*!
  \brief Sendet eine Wort-Pause (Space)
  
  \param gen Zeiger auf Generator-Struktur
  \return 0 bei Erfolg, 1 wenn Generator beschäftigt
*/
uint8_t generator_send_space(morse_generator* gen);

/*!
  \brief Verarbeitet einen Tick (wird alle 1ms aufgerufen)
  
  \param gen Zeiger auf Generator-Struktur
  \return Aktueller Pin-Wert (0 oder 1)
*/
uint8_t generator_process_tick(morse_generator* gen);

/*!
  \brief Prüft ob Generator beschäftigt ist
  
  \param gen Zeiger auf Generator-Struktur
  \return 1 wenn beschäftigt, 0 wenn bereit
*/
uint8_t generator_is_busy(morse_generator* gen);

/*!
  \brief Stoppt den Generator
  
  \param gen Zeiger auf Generator-Struktur
*/
void generator_stop(morse_generator* gen);

/* Modulmethoden / Definitionen: Ende                                         */
#endif // _MODUL_MORSE_GENERATOR_H
