/*!
  \file modul-encoder-hardware.h
  \brief Hardware-abhängige Definitionen für Encoder

  \details Modul Encoder-Hardware
  
  Team: es2025_24
  
  \author Emeric Tcholagheu
  \author Joyce Sonkwe
*/

#ifndef _MODUL_ENCODER_HARDWARE_H
#define _MODUL_ENCODER_HARDWARE_H 1

/* Importe: Beginn                                                            */

// hardware-unabhängiger Code
#include "modul-encoder.h"
// für uint8_t
#include <inttypes.h>

/* Importe: Ende                                                              */
/*----------------------------------------------------------------------------*/
/* Modulmethoden / Definitionen: Beginn                                       */

/*!
  \brief Initialisiert das Modul.

  \details Initialisiert Encoder (minimal, da keine Hardware nötig)

  \return möglicher Fehlercode
  \retval 0 kein Fehler
*/
uint8_t modul_encoder_init(void);

/*!
  \brief Betreibt das Modul.

  \details Wird von run() aufgerufen (minimal)

  \return möglicher Fehlercode
  \retval 0 kein Fehler
*/
uint8_t modul_encoder_run(void);

/* Modulmethoden / Definitionen: Ende                                         */
#endif // _MODUL_ENCODER_HARDWARE_H
