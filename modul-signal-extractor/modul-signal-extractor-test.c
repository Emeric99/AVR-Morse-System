/*!
  \file modul-signal-extractor-test.c
  \brief Testet den Signal-Extractor
*/

#include "modul-signal-extractor.h"
#include <libunittester/unittester.h>
#include <stdio.h>

/*----------------------------------------------------------------------------*/
/* Testfälle: Beginn                                                          */

int test_init(void)
{
  signal_extractor ext;
  extractor_init(&ext);
  
  assertEquals(0, ext.state, "state sollte 0 (IDLE) sein");
  assertEquals(0, ext.current_time, "current_time sollte 0 sein");
  assertEquals(0, ext.last_pin_value, "last_pin_value sollte 0 sein");
  assertEquals(0, ext.symbol_count, "symbol_count sollte 0 sein");
  assertEquals(0, ext.word_complete, "word_complete sollte 0 sein");
  
  return 0;
}

int test_dit_erkennung(void)
{
  signal_extractor ext;
  extractor_init(&ext);
  
  // Simuliere DIT: 1 Tick HIGH
  uint8_t result = extractor_process_sample(&ext, 1);  // LOW→HIGH
  assertEquals(0, result, "Noch kein Zeichen komplett");
  
  result = extractor_process_sample(&ext, 0);  // HIGH→LOW nach 1 Tick
  assertEquals(0, result, "Noch kein Zeichen komplett");
  assertEquals(1, ext.symbol_count, "Sollte 1 Symbol haben");
  assertEquals(MORSE_DIT, ext.symbols[0], "Symbol sollte DIT sein");
  
  // Warte auf Zeichen-Ende (3 Ticks Pause)
  result = extractor_process_sample(&ext, 0);  // Tick 1
  assertEquals(0, result, "Noch kein Zeichen komplett");
  result = extractor_process_sample(&ext, 0);  // Tick 2
  assertEquals(0, result, "Noch kein Zeichen komplett");
  result = extractor_process_sample(&ext, 0);  // Tick 3
  assertEquals(1, result, "Zeichen sollte komplett sein");
  
  // Hole Symbole
  MorseSymbol symbols[8];
  uint8_t count = extractor_get_symbols(&ext, symbols);
  assertEquals(1, count, "Count sollte 1 sein");
  assertEquals(MORSE_DIT, symbols[0], "Symbol sollte DIT sein");
  
  return 0;
}

int test_dah_erkennung(void)
{
  signal_extractor ext;
  extractor_init(&ext);
  
  // Simuliere DAH: 3 Ticks HIGH
  extractor_process_sample(&ext, 1);  // LOW→HIGH
  extractor_process_sample(&ext, 1);  // Tick 1
  extractor_process_sample(&ext, 1);  // Tick 2
  extractor_process_sample(&ext, 0);  // HIGH→LOW nach 3 Ticks
  
  assertEquals(1, ext.symbol_count, "Sollte 1 Symbol haben");
  assertEquals(MORSE_DAH, ext.symbols[0], "Symbol sollte DAH sein");
  
  // Warte auf Zeichen-Ende
  extractor_process_sample(&ext, 0);
  extractor_process_sample(&ext, 0);
  uint8_t result = extractor_process_sample(&ext, 0);
  assertEquals(1, result, "Zeichen sollte komplett sein");
  
  // Hole Symbole
  MorseSymbol symbols[8];
  uint8_t count = extractor_get_symbols(&ext, symbols);
  assertEquals(1, count, "Count sollte 1 sein");
  assertEquals(MORSE_DAH, symbols[0], "Symbol sollte DAH sein");
  
  return 0;
}

int test_s_dit_dit_dit(void)
{
  signal_extractor ext;
  extractor_init(&ext);
  
  // S = Dit Dit Dit
  
  // Dit 1
  extractor_process_sample(&ext, 1);  // HIGH
  extractor_process_sample(&ext, 0);  // LOW
  extractor_process_sample(&ext, 0);  // Pause
  
  // Dit 2
  extractor_process_sample(&ext, 1);  // HIGH
  extractor_process_sample(&ext, 0);  // LOW
  extractor_process_sample(&ext, 0);  // Pause
  
  // Dit 3
  extractor_process_sample(&ext, 1);  // HIGH
  extractor_process_sample(&ext, 0);  // LOW
  
  // Zeichen-Ende (3 Ticks)
  extractor_process_sample(&ext, 0);
  extractor_process_sample(&ext, 0);
  uint8_t result = extractor_process_sample(&ext, 0);
  
  assertEquals(1, result, "S sollte komplett sein");
  assertEquals(3, ext.symbol_count, "Sollte 3 Symbole haben");
  
  // Hole Symbole
  MorseSymbol symbols[8];
  uint8_t count = extractor_get_symbols(&ext, symbols);
  assertEquals(3, count, "Count sollte 3 sein");
  assertEquals(MORSE_DIT, symbols[0], "Symbol 0 sollte DIT sein");
  assertEquals(MORSE_DIT, symbols[1], "Symbol 1 sollte DIT sein");
  assertEquals(MORSE_DIT, symbols[2], "Symbol 2 sollte DIT sein");
  
  return 0;
}

int test_o_dah_dah_dah(void)
{
  signal_extractor ext;
  extractor_init(&ext);
  
  // O = Dah Dah Dah
  
  // Dah 1
  extractor_process_sample(&ext, 1);  // HIGH
  extractor_process_sample(&ext, 1);
  extractor_process_sample(&ext, 1);
  extractor_process_sample(&ext, 0);  // LOW
  extractor_process_sample(&ext, 0);  // Pause
  
  // Dah 2
  extractor_process_sample(&ext, 1);  // HIGH
  extractor_process_sample(&ext, 1);
  extractor_process_sample(&ext, 1);
  extractor_process_sample(&ext, 0);  // LOW
  extractor_process_sample(&ext, 0);  // Pause
  
  // Dah 3
  extractor_process_sample(&ext, 1);  // HIGH
  extractor_process_sample(&ext, 1);
  extractor_process_sample(&ext, 1);
  extractor_process_sample(&ext, 0);  // LOW
  
  // Zeichen-Ende
  extractor_process_sample(&ext, 0);
  extractor_process_sample(&ext, 0);
  uint8_t result = extractor_process_sample(&ext, 0);
  
  assertEquals(1, result, "O sollte komplett sein");
  
  // Hole Symbole
  MorseSymbol symbols[8];
  uint8_t count = extractor_get_symbols(&ext, symbols);
  assertEquals(3, count, "Count sollte 3 sein");
  assertEquals(MORSE_DAH, symbols[0], "Symbol 0 sollte DAH sein");
  assertEquals(MORSE_DAH, symbols[1], "Symbol 1 sollte DAH sein");
  assertEquals(MORSE_DAH, symbols[2], "Symbol 2 sollte DAH sein");
  
  return 0;
}

int test_word_space(void)
{
  signal_extractor ext;
  extractor_init(&ext);
  
  // Dit: HIGH pendant 1 tick
  extractor_process_sample(&ext, 1);  // Tick 1: LOW→HIGH
  extractor_process_sample(&ext, 0);  // Tick 2: HIGH→LOW, DIT erkannt
  
  // Jetzt LOW-Phase für Wort-Pause
  // Wir brauchen >= 7 Ticks LOW für word_complete
  extractor_process_sample(&ext, 0);  // Tick 3: pause=1
  extractor_process_sample(&ext, 0);  // Tick 4: pause=2
  extractor_process_sample(&ext, 0);  // Tick 5: pause=3 → char_complete
  extractor_process_sample(&ext, 0);  // Tick 6: pause=4
  extractor_process_sample(&ext, 0);  // Tick 7: pause=5
  extractor_process_sample(&ext, 0);  // Tick 8: pause=6
  uint8_t result = extractor_process_sample(&ext, 0);  // Tick 9: pause=7 → word_complete
  
  assertEquals(1, result, "Char complete sollte 1 sein");
  assertEquals(1, extractor_is_word_complete(&ext), "Word complete sollte 1 sein");
  
  return 0;
}

int test_ungueltige_dauer(void)
{
  signal_extractor ext;
  extractor_init(&ext);
  
  // Zu langes Signal (5 Ticks)
  extractor_process_sample(&ext, 1);
  for (uint8_t i = 0; i < 5; i++)
  {
    extractor_process_sample(&ext, 1);
  }
  extractor_process_sample(&ext, 0);
  
  // Sollte Reset ausgelöst haben
  assertEquals(0, ext.symbol_count, "Symbol_count sollte 0 sein (Reset)");
  
  return 0;
}

int test_reset(void)
{
  signal_extractor ext;
  extractor_init(&ext);
  
  // Füge Symbole hinzu
  extractor_process_sample(&ext, 1);
  extractor_process_sample(&ext, 0);
  
  assertEquals(1, ext.symbol_count, "Sollte 1 Symbol haben");
  
  // Reset
  extractor_reset(&ext);
  
  assertEquals(0, ext.symbol_count, "symbol_count sollte 0 sein");
  assertEquals(STATE_IDLE, ext.state, "state sollte IDLE sein");
  assertEquals(0, ext.word_complete, "word_complete sollte 0 sein");
  
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
        .name = "Initialisierung",
        .testMethod = test_init,
      },
      {
        .name = "DIT Erkennung",
        .testMethod = test_dit_erkennung,
      },
      {
        .name = "DAH Erkennung",
        .testMethod = test_dah_erkennung,
      },
      {
        .name = "S (Dit-Dit-Dit)",
        .testMethod = test_s_dit_dit_dit,
      },
      {
        .name = "O (Dah-Dah-Dah)",
        .testMethod = test_o_dah_dah_dah,
      },
      {
        .name = "Word Space",
        .testMethod = test_word_space,
      },
      {
        .name = "Ungueltige Dauer",
        .testMethod = test_ungueltige_dauer,
      },
      {
        .name = "Reset",
        .testMethod = test_reset,
      },
    };
    TestSuite suite = {
      .name = "Signal-Extractor Tests",
      .testsToRunLength = 8,
      .testsToRun = tests,
    };
    return testerRunSuite(&suite);
  }
  return configErrors;
}

/* Testsammlung: Ende                                                         */
// EOF
