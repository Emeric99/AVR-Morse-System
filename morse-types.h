/*!
  \file morse-types.h
  \brief Définitions communes pour tous les modules Morse
  
  \details Types et constantes partagés entre:
  - modul-signal-extractor
  - modul-decoder
  - modul-encoder
  - modul-morse-generator

  \author Emeric Tcholagheu
  \author Joyce Sonkwe
*/

#ifndef _MORSE_TYPES_H
#define _MORSE_TYPES_H 1

/* Importe: Beginn                                                            */
#include <inttypes.h>
/* Importe: Ende                                                              */

/*----------------------------------------------------------------------------*/
/* Datenstrukturen: Beginn                                                    */

/*!
  \brief Morse-Symbol Typ (DIT oder DAH)
  
  \details Wird von allen Morse-Modulen verwendet
*/
typedef enum {
  MORSE_DIT = 0,  /* Kurz (·) - 1 Zeiteinheit */
  MORSE_DAH = 1   /* Lang (−) - 3 Zeiteinheiten */
} MorseSymbol;

/* Datenstrukturen: Ende                                                      */

#endif // _MORSE_TYPES_H
