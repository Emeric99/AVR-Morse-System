/*!
  \file modul-signal-extractor-hardware.h
  \brief Hardware-abhängige Definitionen für Signal-Extractor

  \details Modul Signal-Extractor-Hardware
  
  Aufgabe: Hardware-Schnittstelle für Signal-Extractor-Modul
  
  Team: es2025_24
  
  \author Emeric Tcholagheu
  \author Joyce Sonkwe
*/

#ifndef _MODUL_SIGNAL_EXTRACTOR_HARDWARE_H
#define _MODUL_SIGNAL_EXTRACTOR_HARDWARE_H 1

/* Importe: Beginn                                                            */

// hardware-unabhängiger Code
#include "modul-signal-extractor.h"
// für uint8_t
#include <inttypes.h>

/* Importe: Ende                                                              */
/*----------------------------------------------------------------------------*/
/* Modulmethoden / Definitionen: Beginn                                       */

/*!
  \brief Initialisiert das Modul.

  \details Initialisiert Pin-Eingang für Morse-Signal (PINC.0)

  \return möglicher Fehlercode
  \retval 0 kein Fehler
*/
uint8_t modul_signal_extractor_init(void);

/*!
  \brief Betreibt das Modul.

  \details Wird vom Timer-Interrupt (100Hz) aufgerufen

  \return möglicher Fehlercode
  \retval 0 kein Fehler
*/
uint8_t modul_signal_extractor_run(void);

/*!
  \brief Gibt die zuletzt extrahierten Symbole zurück

  \param symbols Array für Ausgabe-Symbole (min. 8 Elemente)
  \return Anzahl Symbole
*/
uint8_t signal_extractor_get_last_symbols(MorseSymbol* symbols);

/*!
  \brief Prüft ob Wort-Pause erkannt wurde

  \return 1 wenn Wort komplett, 0 sonst
*/
uint8_t signal_extractor_is_word_complete_hw(void);

/*!
  \brief Setzt den Extractor zurück für nächstes Zeichen
*/
void signal_extractor_reset_hw(void);

/* Modulmethoden / Definitionen: Ende                                         */
#endif // _MODUL_SIGNAL_EXTRACTOR_HARDWARE_H
