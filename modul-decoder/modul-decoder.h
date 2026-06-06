/*!
  \file modul-decoder.h
  \brief Hardware-unabhängige Definitionen für Morse-Decoder
 
  \details Dekodiert Morse-Signale (Dit/Dah) zu ASCII-Zeichen

  \author Dein Team
*/

#ifndef _MODUL_DECODER_H
#define _MODUL_DECODER_H 1

/* Importe: Beginn                                                            */
#include <inttypes.h>
/* Importe: Ende                                                              */

/*----------------------------------------------------------------------------*/
/* Datenstrukturen: Beginn                                                    */

/*!
  \brief Morse-Decoder Status
*/
typedef struct morse_decoder
{
  uint8_t pattern;  // Bit-Pattern: 0=Dit, 1=Dah (LSB first)
  uint8_t length;   // Anzahl Dit/Dah (0-5)
} morse_decoder;

/* Datenstrukturen: Ende                                                      */
/*----------------------------------------------------------------------------*/
/* Modulmethoden / Definitionen: Beginn                                       */

/*!
  \brief Initialisiert den Decoder
  
  \param dec Zeiger auf Decoder-Struktur
  \return 0 bei Erfolg
*/
uint8_t decoder_init(morse_decoder* dec);

/*!
  \brief Fügt ein Dit hinzu
  
  \param dec Zeiger auf Decoder-Struktur
  \return 0 bei Erfolg, 1 wenn zu viele Elemente
*/
uint8_t decoder_add_dit(morse_decoder* dec);

/*!
  \brief Fügt ein Dah hinzu
  
  \param dec Zeiger auf Decoder-Struktur
  \return 0 bei Erfolg, 1 wenn zu viele Elemente
*/
uint8_t decoder_add_dah(morse_decoder* dec);

/*!
  \brief Dekodiert das aktuelle Pattern zu einem Zeichen
  
  \param dec Zeiger auf Decoder-Struktur
  \return ASCII-Zeichen (A-Z, 0-9) oder '?' wenn unbekannt
*/
char decoder_decode(morse_decoder* dec);

/*!
  \brief Setzt den Decoder zurück
  
  \param dec Zeiger auf Decoder-Struktur
*/
void decoder_reset(morse_decoder* dec);

/* Modulmethoden / Definitionen: Ende                                         */
#endif // _MODUL_DECODER_H
