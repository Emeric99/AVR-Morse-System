/*!
  \file modul-encoder-test.c
  \brief Testet den Morse-Encoder
*/

#include "modul-encoder.h"
#include <libunittester/unittester.h>
#include <stdio.h>

/*----------------------------------------------------------------------------*/
/* Testfälle: Beginn                                                          */

int test_encode_s(void)
{
  MorseSymbol symbols[5];
  uint8_t length;
  
  uint8_t result = encoder_encode_char('S', symbols, &length);
  
  assertEquals(0, result, "Sollte erfolgreich sein");
  assertEquals(3, length, "S hat 3 Symbole");
  assertEquals(MORSE_DIT, symbols[0], "Symbol 0 sollte DIT sein");
  assertEquals(MORSE_DIT, symbols[1], "Symbol 1 sollte DIT sein");
  assertEquals(MORSE_DIT, symbols[2], "Symbol 2 sollte DIT sein");
  
  return 0;
}

int test_encode_o(void)
{
  MorseSymbol symbols[5];
  uint8_t length;
  
  uint8_t result = encoder_encode_char('O', symbols, &length);
  
  assertEquals(0, result, "Sollte erfolgreich sein");
  assertEquals(3, length, "O hat 3 Symbole");
  assertEquals(MORSE_DAH, symbols[0], "Symbol 0 sollte DAH sein");
  assertEquals(MORSE_DAH, symbols[1], "Symbol 1 sollte DAH sein");
  assertEquals(MORSE_DAH, symbols[2], "Symbol 2 sollte DAH sein");
  
  return 0;
}

int test_encode_a(void)
{
  MorseSymbol symbols[5];
  uint8_t length;
  
  uint8_t result = encoder_encode_char('A', symbols, &length);
  
  assertEquals(0, result, "Sollte erfolgreich sein");
  assertEquals(2, length, "A hat 2 Symbole");
  assertEquals(MORSE_DIT, symbols[0], "Symbol 0 sollte DIT sein");
  assertEquals(MORSE_DAH, symbols[1], "Symbol 1 sollte DAH sein");
  
  return 0;
}

int test_encode_lowercase(void)
{
  MorseSymbol symbols1[5];
  MorseSymbol symbols2[5];
  uint8_t length1, length2;
  
  encoder_encode_char('s', symbols1, &length1);
  encoder_encode_char('S', symbols2, &length2);
  
  assertEquals(length1, length2, "Länge sollte gleich sein");
  assertEquals(symbols1[0], symbols2[0], "Sollte gleich encodiert werden");
  
  return 0;
}

int test_encode_number(void)
{
  MorseSymbol symbols[5];
  uint8_t length;
  
  uint8_t result = encoder_encode_char('5', symbols, &length);
  
  assertEquals(0, result, "Sollte erfolgreich sein");
  assertEquals(5, length, "5 hat 5 Symbole");
  assertEquals(MORSE_DIT, symbols[0], "Symbol 0 sollte DIT sein");
  assertEquals(MORSE_DIT, symbols[1], "Symbol 1 sollte DIT sein");
  assertEquals(MORSE_DIT, symbols[2], "Symbol 2 sollte DIT sein");
  assertEquals(MORSE_DIT, symbols[3], "Symbol 3 sollte DIT sein");
  assertEquals(MORSE_DIT, symbols[4], "Symbol 4 sollte DIT sein");
  
  return 0;
}

int test_encode_space(void)
{
  MorseSymbol symbols[5];
  uint8_t length;
  
  uint8_t result = encoder_encode_char(' ', symbols, &length);
  
  assertEquals(0, result, "Sollte erfolgreich sein");
  assertEquals(0, length, "Space hat 0 Symbole");
  
  return 0;
}

int test_encode_unsupported(void)
{
  MorseSymbol symbols[5];
  uint8_t length;
  
  uint8_t result = encoder_encode_char('$', symbols, &length);
  
  assertEquals(1, result, "Sollte Fehler zurückgeben");
  assertEquals(0, length, "Length sollte 0 sein");
  
  return 0;
}

int test_is_supported(void)
{
  assertEquals(1, encoder_is_supported('A'), "A sollte unterstützt sein");
  assertEquals(1, encoder_is_supported('z'), "z sollte unterstützt sein");
  assertEquals(1, encoder_is_supported('5'), "5 sollte unterstützt sein");
  assertEquals(1, encoder_is_supported(' '), "Space sollte unterstützt sein");
  assertEquals(0, encoder_is_supported('$'), "$ sollte nicht unterstützt sein");
  assertEquals(0, encoder_is_supported('@'), "@ sollte nicht unterstützt sein");
  
  return 0;
}





/* Testfälle: Ende                                                            */
/*----------------------------------------------------------------------------*/
/* Testsammlung: Beginn                                                       */

int main(int argc, char** argv)
{
  int configErrors = testerConfigure(argc, argv);
  if (!configErrors)
  {
    CommonTest tests[] = {
      {
        .name = "Encode S",
        .testMethod = test_encode_s,
      },
      {
        .name = "Encode O",
        .testMethod = test_encode_o,
      },
      {
        .name = "Encode A",
        .testMethod = test_encode_a,
      },
      {
        .name = "Lowercase wird zu Uppercase",
        .testMethod = test_encode_lowercase,
      },
      {
        .name = "Encode Zahl 5",
        .testMethod = test_encode_number,
      },
      {
        .name = "Encode Space",
        .testMethod = test_encode_space,
      },
      {
        .name = "Unsupported Character",
        .testMethod = test_encode_unsupported,
      },
      {
        .name = "Is Supported",
        .testMethod = test_is_supported,
      },
    };
    TestSuite suite = {
      .name = "Encoder Tests",
      .testsToRunLength = 8,
      .testsToRun = tests,
    };
    return testerRunSuite(&suite);
  }
  return configErrors;
}

/* Testsammlung: Ende                                                         */
// EOF
