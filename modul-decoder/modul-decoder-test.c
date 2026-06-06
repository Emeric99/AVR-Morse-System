/*!
  \file modul-decoder-test.c
  \brief Testet den Morse-Decoder
*/

#include "modul-decoder.h"
#include <libunittester/unittester.h>
#include <stdio.h>

/*----------------------------------------------------------------------------*/
/* Testfälle: Beginn                                                          */

int test_init(void)
{
  morse_decoder dec;
  decoder_init(&dec);
  
  assertEquals(0, dec.pattern, "Pattern sollte 0 sein");
  assertEquals(0, dec.length, "Length sollte 0 sein");
  
  return 0;
}

int test_decode_E(void)
{
  morse_decoder dec;
  decoder_init(&dec);
  
  // E = .
  decoder_add_dit(&dec);
  
  assertEquals('E', decoder_decode(&dec), "Sollte 'E' sein");
  
  return 0;
}

int test_decode_T(void)
{
  morse_decoder dec;
  decoder_init(&dec);
  
  // T = -
  decoder_add_dah(&dec);
  
  assertEquals('T', decoder_decode(&dec), "Sollte 'T' sein");
  
  return 0;
}

int test_decode_I(void)
{
  morse_decoder dec;
  decoder_init(&dec);
  
  // I = ..
  decoder_add_dit(&dec);
  decoder_add_dit(&dec);
  
  assertEquals('I', decoder_decode(&dec), "Sollte 'I' sein");
  
  return 0;
}

int test_decode_A(void)
{
  morse_decoder dec;
  decoder_init(&dec);
  
  // A = .-
  decoder_add_dit(&dec);
  decoder_add_dah(&dec);
  
  assertEquals('A', decoder_decode(&dec), "Sollte 'A' sein");
  
  return 0;
}

int test_decode_N(void)
{
  morse_decoder dec;
  decoder_init(&dec);
  
  // N = -.
  decoder_add_dah(&dec);
  decoder_add_dit(&dec);
  
  assertEquals('N', decoder_decode(&dec), "Sollte 'N' sein");
  
  return 0;
}

int test_decode_M(void)
{
  morse_decoder dec;
  decoder_init(&dec);
  
  // M = --
  decoder_add_dah(&dec);
  decoder_add_dah(&dec);
  
  assertEquals('M', decoder_decode(&dec), "Sollte 'M' sein");
  
  return 0;
}

int test_decode_S(void)
{
  morse_decoder dec;
  decoder_init(&dec);
  
  // S = ...
  decoder_add_dit(&dec);
  decoder_add_dit(&dec);
  decoder_add_dit(&dec);
  
  assertEquals('S', decoder_decode(&dec), "Sollte 'S' sein");
  
  return 0;
}

int test_decode_O(void)
{
  morse_decoder dec;
  decoder_init(&dec);
  
  // O = ---
  decoder_add_dah(&dec);
  decoder_add_dah(&dec);
  decoder_add_dah(&dec);
  
  assertEquals('O', decoder_decode(&dec), "Sollte 'O' sein");
  
  return 0;
}

int test_decode_H(void)
{
  morse_decoder dec;
  decoder_init(&dec);
  
  // H = ....
  decoder_add_dit(&dec);
  decoder_add_dit(&dec);
  decoder_add_dit(&dec);
  decoder_add_dit(&dec);
  
  assertEquals('H', decoder_decode(&dec), "Sollte 'H' sein");
  
  return 0;
}

int test_decode_5(void)
{
  morse_decoder dec;
  decoder_init(&dec);
  
  // 5 = .....
  decoder_add_dit(&dec);
  decoder_add_dit(&dec);
  decoder_add_dit(&dec);
  decoder_add_dit(&dec);
  decoder_add_dit(&dec);
  
  assertEquals('5', decoder_decode(&dec), "Sollte '5' sein");
  
  return 0;
}

int test_decode_0(void)
{
  morse_decoder dec;
  decoder_init(&dec);
  
  // 0 = -----
  decoder_add_dah(&dec);
  decoder_add_dah(&dec);
  decoder_add_dah(&dec);
  decoder_add_dah(&dec);
  decoder_add_dah(&dec);
  
  assertEquals('0', decoder_decode(&dec), "Sollte '0' sein");
  
  return 0;
}

int test_decode_unknown(void)
{
  morse_decoder dec;
  decoder_init(&dec);
  
  // Ungültiges Pattern: ......
  assertEquals(0, decoder_add_dit(&dec), "erstes Signal ok");
  assertEquals(0, decoder_add_dit(&dec), "zweites Signal ok");
  assertEquals(0, decoder_add_dit(&dec), "drittes Signal ok");
  assertEquals(0, decoder_add_dit(&dec), "viertes Signal ok");
  assertEquals(0, decoder_add_dit(&dec), "fünftes Signal ok");
  // 6 Elemente = ungültig
  assertEquals(1, decoder_add_dah(&dec), "sechstes Signal nicht ok");
  
  // assertEqualsChar('?', decoder_decode(&dec), "Sollte '?' sein");
  
  return 0;
}

int test_reset(void)
{
  morse_decoder dec;
  decoder_init(&dec);
  
  // Füge etwas hinzu
  decoder_add_dit(&dec);
  decoder_add_dah(&dec);
  
  // Reset
  decoder_reset(&dec);
  
  assertEquals(0, dec.pattern, "Pattern sollte 0 sein");
  assertEquals(0, dec.length, "Length sollte 0 sein");
  
  return 0;
}

int test_overflow(void)
{
  morse_decoder dec;
  decoder_init(&dec);
  
  // Füge 5 Elemente hinzu (Maximum)
  decoder_add_dit(&dec);
  decoder_add_dit(&dec);
  decoder_add_dit(&dec);
  decoder_add_dit(&dec);
  decoder_add_dit(&dec);
  
  // Versuch ein 6. hinzuzufügen
  assertEquals(1, decoder_add_dit(&dec), "6.-Element: Sollte Fehler zurückgeben");
  assertEquals(1, decoder_add_dit(&dec), "7.-Element: Sollte Fehler zurückgeben");
  assertEquals(1, decoder_add_dit(&dec), "8.-Element: Sollte Fehler zurückgeben");
  assertEquals(1, decoder_add_dit(&dec), "9.-Element: Sollte Fehler zurückgeben");
  assertEquals(9, dec.length, "9.-Element: Length sollte <= 9 bleiben");
  assertEquals(1, decoder_add_dit(&dec), "10.-Element: Sollte Fehler zurückgeben");
  assertEquals(9, dec.length, "10.-Element: Length sollte <= 9 bleiben");
  assertEquals(1, decoder_add_dit(&dec), "11.-Element: Sollte Fehler zurückgeben");
  assertEquals(9, dec.length, "11.-Element: Length sollte <= 9 bleiben");
  
  return 0;
}

/* Testfälle: Ende                                                            */
/*----------------------------------------------------------------------------*/
/* Main: Beginn                                                               */

int main(int argc, char** argv)
{
  int configErrors = testerConfigure(argc, argv);
  if (!configErrors)
  {
    CommonTest tests[] = {
      {
        .name = "Initialisierung",
        .testMethod = test_init,
      },
      {
        .name = "Dekodiere E (.)",
        .testMethod = test_decode_E,
      },
      {
        .name = "Dekodiere T (-)",
        .testMethod = test_decode_T,
      },
      {
        .name = "Dekodiere I (..)",
        .testMethod = test_decode_I,
      },
      {
        .name = "Dekodiere A (.-)",
        .testMethod = test_decode_A,
      },
      {
        .name = "Dekodiere N (-.)",
        .testMethod = test_decode_N,
      },
      {
        .name = "Dekodiere M (--)",
        .testMethod = test_decode_M,
      },
      {
        .name = "Dekodiere S (...)",
        .testMethod = test_decode_S,
      },
      {
        .name = "Dekodiere O (---)",
        .testMethod = test_decode_O,
      },
      {
        .name = "Dekodiere H (....)",
        .testMethod = test_decode_H,
      },
      {
        .name = "Dekodiere 5 (.....)",
        .testMethod = test_decode_5,
      },
      {
        .name = "Dekodiere 0 (-----)",
        .testMethod = test_decode_0,
      },
      {
        .name = "Unbekanntes Pattern",
        .testMethod = test_decode_unknown,
      },
      {
        .name = "Reset",
        .testMethod = test_reset,
      },
      {
        .name = "Overflow (>5 Elemente)",
        .testMethod = test_overflow,
      },
    };
    TestSuite suite = {
      .name = "Decoder-Modul Tests",
      .testsToRunLength = 15,
      .testsToRun = tests,
    };
    return testerRunSuite(&suite);
  }
  return configErrors;
}

/* Main: Ende                                                                 */
// EOF
