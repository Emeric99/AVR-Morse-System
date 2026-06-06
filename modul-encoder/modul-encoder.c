#include "modul-encoder.h"
#include <ctype.h>

/* Modulmethoden / Implementierungen: Beginn                                  */

/* Morse-Code Lookup Table (ITU-R M.1677-1) */
static const MorseEncoding morse_table[] = {
  /* Buchstaben A-Z */
  {'A', {MORSE_DIT, MORSE_DAH}, 2},                              // .-
  {'B', {MORSE_DAH, MORSE_DIT, MORSE_DIT, MORSE_DIT}, 4},        // -...
  {'C', {MORSE_DAH, MORSE_DIT, MORSE_DAH, MORSE_DIT}, 4},        // -.-.
  {'D', {MORSE_DAH, MORSE_DIT, MORSE_DIT}, 3},                   // -..
  {'E', {MORSE_DIT}, 1},                                          // .
  {'F', {MORSE_DIT, MORSE_DIT, MORSE_DAH, MORSE_DIT}, 4},        // ..-.
  {'G', {MORSE_DAH, MORSE_DAH, MORSE_DIT}, 3},                   // --.
  {'H', {MORSE_DIT, MORSE_DIT, MORSE_DIT, MORSE_DIT}, 4},        // ....
  {'I', {MORSE_DIT, MORSE_DIT}, 2},                              // ..
  {'J', {MORSE_DIT, MORSE_DAH, MORSE_DAH, MORSE_DAH}, 4},        // .---
  {'K', {MORSE_DAH, MORSE_DIT, MORSE_DAH}, 3},                   // -.-
  {'L', {MORSE_DIT, MORSE_DAH, MORSE_DIT, MORSE_DIT}, 4},        // .-..
  {'M', {MORSE_DAH, MORSE_DAH}, 2},                              // --
  {'N', {MORSE_DAH, MORSE_DIT}, 2},                              // -.
  {'O', {MORSE_DAH, MORSE_DAH, MORSE_DAH}, 3},                   // ---
  {'P', {MORSE_DIT, MORSE_DAH, MORSE_DAH, MORSE_DIT}, 4},        // .--.
  {'Q', {MORSE_DAH, MORSE_DAH, MORSE_DIT, MORSE_DAH}, 4},        // --.-
  {'R', {MORSE_DIT, MORSE_DAH, MORSE_DIT}, 3},                   // .-.
  {'S', {MORSE_DIT, MORSE_DIT, MORSE_DIT}, 3},                   // ...
  {'T', {MORSE_DAH}, 1},                                          // -
  {'U', {MORSE_DIT, MORSE_DIT, MORSE_DAH}, 3},                   // ..-
  {'V', {MORSE_DIT, MORSE_DIT, MORSE_DIT, MORSE_DAH}, 4},        // ...-
  {'W', {MORSE_DIT, MORSE_DAH, MORSE_DAH}, 3},                   // .--
  {'X', {MORSE_DAH, MORSE_DIT, MORSE_DIT, MORSE_DAH}, 4},        // -..-
  {'Y', {MORSE_DAH, MORSE_DIT, MORSE_DAH, MORSE_DAH}, 4},        // -.--
  {'Z', {MORSE_DAH, MORSE_DAH, MORSE_DIT, MORSE_DIT}, 4},        // --..
  
  /* Zahlen 0-9 */
  {'0', {MORSE_DAH, MORSE_DAH, MORSE_DAH, MORSE_DAH, MORSE_DAH}, 5},  // -----
  {'1', {MORSE_DIT, MORSE_DAH, MORSE_DAH, MORSE_DAH, MORSE_DAH}, 5},  // .----
  {'2', {MORSE_DIT, MORSE_DIT, MORSE_DAH, MORSE_DAH, MORSE_DAH}, 5},  // ..---
  {'3', {MORSE_DIT, MORSE_DIT, MORSE_DIT, MORSE_DAH, MORSE_DAH}, 5},  // ...--
  {'4', {MORSE_DIT, MORSE_DIT, MORSE_DIT, MORSE_DIT, MORSE_DAH}, 5},  // ....-
  {'5', {MORSE_DIT, MORSE_DIT, MORSE_DIT, MORSE_DIT, MORSE_DIT}, 5},  // .....
  {'6', {MORSE_DAH, MORSE_DIT, MORSE_DIT, MORSE_DIT, MORSE_DIT}, 5},  // -....
  {'7', {MORSE_DAH, MORSE_DAH, MORSE_DIT, MORSE_DIT, MORSE_DIT}, 5},  // --...
  {'8', {MORSE_DAH, MORSE_DAH, MORSE_DAH, MORSE_DIT, MORSE_DIT}, 5},  // ---..
  {'9', {MORSE_DAH, MORSE_DAH, MORSE_DAH, MORSE_DAH, MORSE_DIT}, 5},  // ----.
};

/* Anzahl Einträge in der Tabelle */
static const uint8_t morse_table_size = sizeof(morse_table) / sizeof(MorseEncoding);

uint8_t encoder_encode_char(char ascii, MorseSymbol* symbols, uint8_t* length)
{
  /* Konvertiere zu Großbuchstaben */
  char upper = toupper(ascii);
  
  /* Space hat keine Symbole (wird als Pause behandelt) */
  if (upper == ' ')
  {
    *length = 0;
    return 0;
  }
  
  /* Suche in der Tabelle */
  for (uint8_t i = 0; i < morse_table_size; i++)
  {
    if (morse_table[i].ascii == upper)
    {
      /* Gefunden! Kopiere Symbole */
      *length = morse_table[i].length;
      for (uint8_t j = 0; j < morse_table[i].length; j++)
      {
        symbols[j] = morse_table[i].symbols[j];
      }
      return 0;  /* Erfolg */
    }
  }
  
  /* Zeichen nicht gefunden */
  *length = 0;
  return 1;  /* Fehler */
}

uint8_t encoder_is_supported(char ascii)
{
  char upper = toupper(ascii);
  
  /* Space ist unterstützt */
  if (upper == ' ')
  {
    return 1;
  }
  
  /* Suche in der Tabelle */
  for (uint8_t i = 0; i < morse_table_size; i++)
  {
    if (morse_table[i].ascii == upper)
    {
      return 1;  /* Unterstützt */
    }
  }
  
  return 0;  /* Nicht unterstützt */
}

/* Modulmethoden / Implementierungen: Ende                                    */
// EOF
