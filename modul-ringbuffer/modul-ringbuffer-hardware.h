/*!
  \file modul-ringbuffer-hardware.h
  \brief Hardware-abhängige Definitionen für das Modul-Ringbuffer.

  \details Modul Ringbuffer-Hardware
  
  Aufgabe: Hardware-Schnittstelle für Ringbuffer-Modul
  
  Team: es2025_24
  
  \author Emeric Tcholagheu
  \author Joyce Sonkwe
*/

#ifndef _MODUL_RINGBUFFER_HARDWARE_H
#define _MODUL_RINGBUFFER_HARDWARE_H 1

/* Importe: Beginn                                                            */

// hardware-unabhängiger Code
#include "modul-ringbuffer.h"
// für uint8_t
#include <inttypes.h>

/* Importe: Ende                                                              */
/*----------------------------------------------------------------------------*/
/* Modulmethoden / Definitionen: Beginn                                       */

/*!
  \brief Initialisiert das Modul.

  \details Für das Ringbuffer-Modul gibt es keine Hardware-Initialisierung.

  \return möglicher Fehlercode
  \retval 0 kein Fehler
*/
uint8_t modul_ringbuffer_init(void);

/*!
  \brief Betreibt das Modul.

  \details Für das Ringbuffer-Modul gibt es keinen kontinuierlichen Betrieb.

  \return möglicher Fehlercode
  \retval 0 kein Fehler
*/
uint8_t modul_ringbuffer_run(void);

/* Modulmethoden / Definitionen: Ende                                         */
#endif // _MODUL_RINGBUFFER_HARDWARE_H
