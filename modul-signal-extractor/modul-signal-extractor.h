/*!
  \file modul-signal-extractor.h
  \brief Hardware-unabhängige Definitionen für Signal-Extractor

  \details Extrahiert Morse-Signale (Dit/Dah) aus Pin-Timing

  \author Emeric Tcholagheu
  \author Joyce Sonkwe
*/

#ifndef _MODUL_SIGNAL_EXTRACTOR_H
#define _MODUL_SIGNAL_EXTRACTOR_H 1

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
  \brief Extractor State Machine
*/
typedef enum {
  STATE_IDLE = 0,
  STATE_SIGNAL_HIGH = 1,
  STATE_SIGNAL_LOW = 2,
  STATE_CHAR_COMPLETE = 3
} ExtractorState;

/*!
  \brief Timing-Schwellwerte
*/
typedef enum {
  TIMING_DIT_MAX = 2,      /* < 2 Ticks = DIT */
  TIMING_DAH_MIN = 2,      /* >= 2 Ticks = DAH */
  TIMING_DAH_MAX = 5,      /* < 5 Ticks gültig */
  TIMING_CHAR_SPACE = 3,   /* >= 3 Ticks = Zeichen-Ende */
  TIMING_WORD_SPACE = 7    /* >= 7 Ticks = Wort-Ende */
} TimingThreshold;

/*!
  \brief Signal-Extractor Status
*/
typedef struct signal_extractor
{
  uint8_t state;              // State Machine
  uint8_t start_time;         // Beginn der aktuellen Phase (Ticks)
  uint8_t current_time;       // Aktueller Tick-Counter
  uint8_t last_pin_value;     // Letzter Pin-Wert (für Flanken-Erkennung)
  MorseSymbol symbols[8];     // Gesammelte Symbole (max 5 für längsten Code)
  uint8_t symbol_count;       // Anzahl Symbole im Buffer
  uint8_t word_complete;      // 1 wenn Wort-Pause erkannt
} signal_extractor;

/* Datenstrukturen: Ende                                                      */
/*----------------------------------------------------------------------------*/
/* Modulmethoden / Definitionen: Beginn                                       */

/*!
  \brief Initialisiert den Signal-Extractor

  \param ext Zeiger auf Extractor-Struktur
  \return 0 bei Erfolg
*/
uint8_t extractor_init(signal_extractor* ext);

/*!
  \brief Verarbeitet ein Pin-Sample

  \param ext Zeiger auf Extractor-Struktur
  \param pin_value Aktueller Pin-Wert (0 oder 1)
  \return 1 wenn Zeichen komplett, 0 sonst
*/
uint8_t extractor_process_sample(signal_extractor* ext, uint8_t pin_value);

/*!
  \brief Gibt die extrahierten Symbole zurück

  \param ext Zeiger auf Extractor-Struktur
  \param output_symbols Array für Ausgabe-Symbole (min. 8 Elemente)
  \return Anzahl Symbole
*/
uint8_t extractor_get_symbols(signal_extractor* ext, MorseSymbol* output_symbols);

/*!
  \brief Prüft ob Wort-Pause erkannt wurde

  \param ext Zeiger auf Extractor-Struktur
  \return 1 wenn Wort komplett, 0 sonst
*/
uint8_t extractor_is_word_complete(signal_extractor* ext);

/*!
  \brief Setzt den Extractor zurück für nächstes Zeichen

  \param ext Zeiger auf Extractor-Struktur
*/
void extractor_reset(signal_extractor* ext);

/* Modulmethoden / Definitionen: Ende                                         */
#endif // _MODUL_SIGNAL_EXTRACTOR_H
