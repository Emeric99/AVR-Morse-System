/*!
  \file modul-display-hardware.h
  \brief Hardware-abhängige Definitionen für 7-Segment-Display
 
  \details Hardware-Ansteuerung für 3-stellige 7-Segment-Anzeige

  \author Dein Team
*/

#ifndef _MODUL_DISPLAY_HARDWARE_H
#define _MODUL_DISPLAY_HARDWARE_H 1

/* Importe: Beginn                                                            */
#include "modul-display.h"
#include <inttypes.h>
/* Importe: Ende                                                              */

/*----------------------------------------------------------------------------*/
/* Modulmethoden / Definitionen: Beginn                                       */

/*!
  \brief Initialisiert die 7-Segment-Hardware
  
  Konfiguriert die Ports für die 7-Segment-Anzeige
  
  \return 0 bei Erfolg
*/
uint8_t modul_display_init(void);

uint8_t modul_display_run(void);

/*!
  \brief Zeigt 3 Zeichen auf der 7-Segment-Anzeige
  
  Diese Funktion muss periodisch aufgerufen werden (z.B. im Timer-Interrupt)
  für Multiplexing der 3 Digits
  
  \param disp Zeiger auf Display-Controller-Struktur
  \return 0 bei Erfolg
*/
uint8_t display_hardware_show(display_controller* disp);

/*!
  \brief Aktualisiert das Display (wird im Timer-ISR aufgerufen)
  
  Multiplext durch die 3 Digits
  
  \param disp Zeiger auf Display-Controller-Struktur
*/
void display_hardware_update(display_controller* disp);

/* Modulmethoden / Definitionen: Ende                                         */
#endif 
