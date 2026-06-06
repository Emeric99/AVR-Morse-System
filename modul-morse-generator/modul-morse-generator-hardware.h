/*!
  \file modul-morse-generator-hardware.h
  \brief Hardware-abhängige Definitionen für Morse-Generator

  \details Modul Morse-Generator-Hardware
  
  Team: es2025_24
  
  \author Emeric Tcholagheu
  \author Joyce Sonkwe
*/

#ifndef _MODUL_MORSE_GENERATOR_HARDWARE_H
#define _MODUL_MORSE_GENERATOR_HARDWARE_H 1

/* Importe: Beginn                                                            */

// hardware-unabhängiger Code
#include "modul-morse-generator.h"
// für uint8_t
#include <inttypes.h>

/* Importe: Ende                                                              */
/*----------------------------------------------------------------------------*/
/* Modulmethoden / Definitionen: Beginn                                       */

/*!
  \brief Initialisiert das Modul.

  \details Initialisiert Output-Pin (PORTC.2) und Timer

  \return möglicher Fehlercode
  \retval 0 kein Fehler
*/
uint8_t modul_morse_generator_init(void);

/*!
  \brief Betreibt das Modul.

  \details Wird von run() aufgerufen

  \return möglicher Fehlercode
  \retval 0 kein Fehler
*/
uint8_t modul_morse_generator_run(void);

/*!
  \brief Sendet Morse-Symbole
  
  \param symbols Array von Symbolen
  \param count Anzahl Symbole
  \return 0 bei Erfolg, 1 wenn beschäftigt
*/
uint8_t morse_generator_send_symbols_hw(const MorseSymbol* symbols, uint8_t count);

/*!
  \brief Sendet Space (Wort-Pause)
  
  \return 0 bei Erfolg, 1 wenn beschäftigt
*/
uint8_t morse_generator_send_space_hw(void);

/*!
  \brief Prüft ob Generator beschäftigt
  
  \return 1 wenn beschäftigt, 0 wenn bereit
*/
uint8_t morse_generator_is_busy_hw(void);

/* Modulmethoden / Definitionen: Ende                                         */
#endif // _MODUL_MORSE_GENERATOR_HARDWARE_H
