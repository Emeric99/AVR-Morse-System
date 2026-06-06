/*!
  \file modul-decoder-hardware.h
  \brief Hardware-abhängige Definitionen für das Modul-decoder.

  \details Modul decoder-Hardware (TODO)
 
  Aufgabe: ... (TODO)
  
  Team: es... (TODO)
 
  \author Maria Messerschmied (TODO)
  \author Hägar Hau-den-Lukas (TODO)
*/

// TODO Benenne decoder um in passenden Modulnamen.

#ifndef _MODUL_decoder_HARDWARE_H
#define _MODUL_decoder_HARDWARE_H 1

/* Importe: Beginn                                                            */

// hardware-unabhängiger Code
#include "modul-decoder.h"
// für uint8_t
#include <inttypes.h>

/* Importe: Ende                                                              */
/*----------------------------------------------------------------------------*/
/* Modulmethoden / Definitionen: Beginn                                       */

/*!
  \brief Initialisiert das Modul.

  Es werden interne Variablen initialisiert und Hardware-Einstellungen
  vorgenommen.

  Initialisierte Timer ...

  Initialisierte Schnittstellen ...

  \return möglicher Fehlercode
  \retval 0 kein Fehler
  \retval !0 es liegt ein Fehler vor, Liste der Fehlercodes (TODO)
*/
uint8_t modul_decoder_init(void);

/*!
  \brief Betreibt das Modul.

  \return möglicher Fehlercode
  \retval 0 kein Fehler
  \retval !0 es liegt ein Fehler vor, Liste der Fehlercodes (TODO)  
*/
uint8_t modul_decoder_run(void);

/* Modulmethoden / Definitionen: Ende                                         */
#endif // _MODUL_decoder_HARDWARE_H

