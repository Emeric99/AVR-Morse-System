/*!
  \file modul-encoder.h
  \brief Hardware-unabhängige Definitionen für Morse-Encoder
 
  \details Encodiert ASCII-Zeichen in Morse-Symbole (DIT/DAH)

  \author Emeric Tcholagheu
  \author Jpyce Sonkwe
*/

#ifndef _MODUL_ENCODER_H
#define _MODUL_ENCODER_H 1

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
  \brief Maximale Anzahl Symbole pro Zeichen
  
  Das längste Zeichen im Morse-Code hat 5 Symbole (z.B. '6' = -....-)
*/
typedef enum {
  MAX_MORSE_SYMBOLS = 5
} EncoderConstants;

/*!
  \brief Morse-Encoding Eintrag (für Lookup-Table)
*/
typedef struct {
  char ascii;                      // ASCII-Zeichen ('A', 'B', etc.)
  MorseSymbol symbols[5];          // Morse-Symbole
  uint8_t length;                  // Anzahl Symbole (1-5)
} MorseEncoding;

/* Datenstrukturen: Ende                                                      */
/*----------------------------------------------------------------------------*/
/* Modulmethoden / Definitionen: Beginn                                       */

/*!
  \brief Encodiert ein ASCII-Zeichen in Morse-Symbole
  
  \param ascii Das zu encodierende Zeichen (A-Z, 0-9, Space)
  \param symbols Array für Ausgabe-Symbole (min. 5 Elemente)
  \param length Zeiger auf Variable für Anzahl Symbole
  \return 0 bei Erfolg, 1 wenn Zeichen nicht unterstützt
*/
uint8_t encoder_encode_char(char ascii, MorseSymbol* symbols, uint8_t* length);

/*!
  \brief Prüft ob ein Zeichen encodierbar ist
  
  \param ascii Das zu prüfende Zeichen
  \return 1 wenn unterstützt, 0 sonst
*/
uint8_t encoder_is_supported(char ascii);

/* Modulmethoden / Definitionen: Ende                                         */
#endif // _MODUL_ENCODER_H
