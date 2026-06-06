#include "modul-decoder.h"

/* Modulmethoden / Implementierungen: Beginn                                  */

/* Lookup-Tabelle für Morse → ASCII                                           */
typedef struct morse_lookup
{
  uint8_t pattern;
  uint8_t length;
  char character;
} morse_lookup;

static const morse_lookup morse_table[] = {
  // Buchstaben A-Z
  {0b10,     2, 'A'},   // .-
  {0b0001,   4, 'B'},   // -...
  {0b0101,   4, 'C'},   // -.-.
  {0b001,    3, 'D'},   // -..
  {0b0,      1, 'E'},   // .
  {0b0100,   4, 'F'},   // ..-.
  {0b011,    3, 'G'},   // --.
  {0b0000,   4, 'H'},   // ....
  {0b00,     2, 'I'},   // ..
  {0b1110,   4, 'J'},   // .---
  {0b101,    3, 'K'},   // -.-
  {0b0010,   4, 'L'},   // .-..
  {0b11,     2, 'M'},   // --
  {0b01,     2, 'N'},   // -.
  {0b111,    3, 'O'},   // ---
  {0b0110,   4, 'P'},   // .--.
  {0b1011,   4, 'Q'},   // --.-
  {0b010,    3, 'R'},   // .-.
  {0b000,    3, 'S'},   // ...
  {0b1,      1, 'T'},   // -
  {0b100,    3, 'U'},   // ..-
  {0b1000,   4, 'V'},   // ...-
  {0b110,    3, 'W'},   // .--
  {0b1001,   4, 'X'},   // -..-
  {0b1101,   4, 'Y'},   // -.--
  {0b0011,   4, 'Z'},   // --..
  
  // Zahlen 0-9
  {0b11111,  5, '0'},   // -----
  {0b11110,  5, '1'},   // .----
  {0b11100,  5, '2'},   // ..---
  {0b11000,  5, '3'},   // ...--
  {0b10000,  5, '4'},   // ....-
  {0b00000,  5, '5'},   // .....
  {0b00001,  5, '6'},   // -....
  {0b00011,  5, '7'},   // --...
  {0b00111,  5, '8'},   // ---..
  {0b01111,  5, '9'},   // ----.
};

static const uint8_t MORSE_TABLE_SIZE = sizeof(morse_table) / sizeof(morse_lookup);
/*----------------------------------------------------------------------------*/

uint8_t decoder_init(morse_decoder* dec)
{
  dec->pattern = 0;
  dec->length = 0;
  return 0;
}

static void increment_dec_length(morse_decoder* dec)
{
  if (dec->length < 9)
  {
    dec->length++;
  }
}

uint8_t decoder_add_dit(morse_decoder* dec)
{
  uint8_t returnCode = 0;
  // Prüfe ob noch Platz (max 5 Elemente)
  // schließe Morse-Code länger als 5 Elemente aus,
  // Satzzeichen, wie Komma, Punkt, ? und "error" im Moment nicht konvertiert
  if (dec->length >= 5)
  {
    returnCode = 1; // Fehler: zu viele Elemente
  }
    // Dit = 0, also nichts tun (Pattern-Bit bleibt 0)
  increment_dec_length(dec);
  return returnCode;
}

uint8_t decoder_add_dah(morse_decoder* dec)
{
  uint8_t returnCode = 0;
  // Prüfe ob noch Platz (max 5 Elemente)
  // schließe Morse-Code länger als 5 Elemente aus,
  // Satzzeichen, wie Komma, Punkt, ? und "error" im Moment nicht konvertiert
  if (dec->length >= 5)
  {
    returnCode = 1; // Fehler: zu viele Elemente
  } else {
    // Dah = 1, also Bit an aktueller Position setzen
    dec->pattern |= (1 << dec->length);
  }
  increment_dec_length(dec);
  
  return returnCode;
}

char decoder_decode(morse_decoder* dec)
{
  // Suche in Lookup-Tabelle
  for (uint8_t i = 0; i < MORSE_TABLE_SIZE; i++)
  {
    if (morse_table[i].pattern == dec->pattern &&
        morse_table[i].length == dec->length)
    {
      return morse_table[i].character;
    }
  }
  
  // Nicht gefunden
  return '?';
}

void decoder_reset(morse_decoder* dec)
{
  dec->pattern = 0;
  dec->length = 0;
}

/* Modulmethoden / Implementierungen: Ende                                    */
// EOF
