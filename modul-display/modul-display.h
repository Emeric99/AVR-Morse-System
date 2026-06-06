/*!
  \file modul-display.h
  \brief Hardware-unabhängige Definitionen für Display
 
  \details Display-Controller für 7-Segment-Anzeige (3 Zeichen)

  \author Dein Team
*/

#ifndef _MODUL_DISPLAY_H
#define _MODUL_DISPLAY_H 1

/* Importe: Beginn                                                            */
#include <inttypes.h>
/* Importe: Ende                                                              */

/*----------------------------------------------------------------------------*/
/* Datenstrukturen: Beginn                                                    */

/*!
  \brief Display-Controller Status
*/
typedef struct display_controller
{
  char window[4];       // 3 Zeichen + \0
  uint8_t scroll_pos;   // Position im Text (für Scrolling)
} display_controller;

/* Datenstrukturen: Ende                                                      */
/*----------------------------------------------------------------------------*/
/* Modulmethoden / Definitionen: Beginn                                       */

/*!
  \brief Initialisiert den Display-Controller
  
  \param disp Zeiger auf Display-Controller-Struktur
  \return 0 bei Erfolg
*/
uint8_t display_init(display_controller* disp);

/*!
  \brief Setzt die anzuzeigenden 3 Zeichen
  
  \param disp Zeiger auf Display-Controller-Struktur
  \param text Zeiger auf Text (mindestens 3 Zeichen oder kürzer mit \0)
  \return 0 bei Erfolg
*/
uint8_t display_set_text(display_controller* disp, const char* text);

/*!
  \brief Gibt die aktuell anzuzeigenden Zeichen zurück
  
  \param disp Zeiger auf Display-Controller-Struktur
  \return Zeiger auf window (3 Zeichen + \0)
*/
char* display_get_window(display_controller* disp);

/*!
  \brief Setzt die Scroll-Position
  
  \param disp Zeiger auf Display-Controller-Struktur
  \param pos Position im Gesamt-Text
*/
void display_set_scroll_pos(display_controller* disp, uint8_t pos);

/*!
  \brief Gibt die aktuelle Scroll-Position zurück
  
  \param disp Zeiger auf Display-Controller-Struktur
  \return Scroll-Position
*/
uint8_t display_get_scroll_pos(display_controller* disp);

/* Modulmethoden / Definitionen: Ende                                         */
#endif // _MODUL_DISPLAY_H
