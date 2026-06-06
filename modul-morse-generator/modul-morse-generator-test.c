/*!
  \file modul-morse-generator-test.c
  \brief Testet den Morse-Generator
*/

#include "modul-morse-generator.h"
#include <libunittester/unittester.h>
#include <stdio.h>

/*----------------------------------------------------------------------------*/
/* Testfälle: Beginn                                                          */

int test_init(void)
{
  morse_generator gen;
  generator_init(&gen);
  
  assertEquals(GEN_STATE_IDLE, gen.state, "State sollte IDLE sein");
  assertEquals(0, gen.is_busy, "Should not be busy");
  assertEquals(0, gen.symbol_count, "Symbol count sollte 0 sein");
  
  return 0;
}

int test_send_dit(void)
{
  morse_generator gen;
  generator_init(&gen);
  
  MorseSymbol symbols[] = {MORSE_DIT};
  uint8_t result = generator_send_symbols(&gen, symbols, 1);
  
  assertEquals(0, result, "Sollte erfolgreich sein");
  assertEquals(1, generator_is_busy(&gen), "Should be busy");
  assertEquals(GEN_STATE_SENDING_SYMBOL, gen.state, "Sollte im SENDING state sein");
  
  return 0;
}

int test_dit_timing(void)
{
  morse_generator gen;
  generator_init(&gen);
  
  MorseSymbol symbols[] = {MORSE_DIT};
  generator_send_symbols(&gen, symbols, 1);
  
  // Tick 0: HIGH
  uint8_t pin = generator_process_tick(&gen);
  assertEquals(1, pin, "Pin sollte HIGH sein");
  assertEquals(GEN_STATE_SENDING_SYMBOL, gen.state, "State SENDING");
  
  // Nach 1 Tick: Übergang zu PAUSE_CHAR
  pin = generator_process_tick(&gen);
  assertEquals(0, pin, "Pin sollte LOW sein (Pause)");
  assertEquals(GEN_STATE_PAUSE_CHAR, gen.state, "State PAUSE_CHAR");
  
  // Nach 3 weiteren Ticks: IDLE
  generator_process_tick(&gen);
  generator_process_tick(&gen);
  pin = generator_process_tick(&gen);
  assertEquals(0, pin, "Pin sollte LOW sein");
  assertEquals(GEN_STATE_IDLE, gen.state, "State sollte IDLE sein");
  assertEquals(0, generator_is_busy(&gen), "Should not be busy");
  
  return 0;
}

int test_dah_timing(void)
{
  morse_generator gen;
  generator_init(&gen);
  
  MorseSymbol symbols[] = {MORSE_DAH};
  generator_send_symbols(&gen, symbols, 1);
  
  // 3 Ticks HIGH für DAH
  uint8_t pin;
  pin = generator_process_tick(&gen);
  assertEquals(1, pin, "Tick 1: HIGH");
  
  pin = generator_process_tick(&gen);
  assertEquals(1, pin, "Tick 2: HIGH");
  
  pin = generator_process_tick(&gen);
  assertEquals(1, pin, "Tick 3: HIGH");
  
  // Nach 3 Ticks: Pause
  pin = generator_process_tick(&gen);
  assertEquals(0, pin, "Tick 4: LOW (Pause)");
  assertEquals(GEN_STATE_PAUSE_CHAR, gen.state, "State PAUSE_CHAR");
  
  return 0;
}

int test_multiple_symbols(void)
{
  morse_generator gen;
  generator_init(&gen);
  
  // S = DIT DIT DIT
  MorseSymbol symbols[] = {MORSE_DIT, MORSE_DIT, MORSE_DIT};
  generator_send_symbols(&gen, symbols, 3);
  
  // DIT 1: 1 tick HIGH
  uint8_t pin = generator_process_tick(&gen);
  assertEquals(1, pin, "DIT 1: HIGH");
  
  // Pause intra: 1 tick LOW
  pin = generator_process_tick(&gen);
  assertEquals(0, pin, "Pause intra");
  assertEquals(GEN_STATE_PAUSE_INTRA, gen.state, "State PAUSE_INTRA");
  
  // DIT 2: 1 tick HIGH
  pin = generator_process_tick(&gen);
  assertEquals(1, pin, "DIT 2: HIGH");
  
  // Pause intra
  pin = generator_process_tick(&gen);
  assertEquals(0, pin, "Pause intra");
  
  // DIT 3: 1 tick HIGH
  pin = generator_process_tick(&gen);
  assertEquals(1, pin, "DIT 3: HIGH");
  
  // Pause char: 3 ticks LOW
  pin = generator_process_tick(&gen);
  assertEquals(0, pin, "Pause char 1");
  assertEquals(GEN_STATE_PAUSE_CHAR, gen.state, "State PAUSE_CHAR");
  
  return 0;
}

int test_send_space(void)
{
  morse_generator gen;
  generator_init(&gen);
  
  uint8_t result = generator_send_space(&gen);
  
  assertEquals(0, result, "Sollte erfolgreich sein");
  assertEquals(1, generator_is_busy(&gen), "Should be busy");
  assertEquals(GEN_STATE_PAUSE_CHAR, gen.state, "State PAUSE_CHAR");
  
  // 7 Ticks für Word-Pause
  for (uint8_t i = 0; i < 7; i++)
  {
    uint8_t pin = generator_process_tick(&gen);
    assertEquals(0, pin, "Pin sollte LOW sein während Space");
  }
  
  assertEquals(GEN_STATE_IDLE, gen.state, "Nach 7 Ticks: IDLE");
  assertEquals(0, generator_is_busy(&gen), "Should not be busy");
  
  return 0;
}

int test_busy_reject(void)
{
  morse_generator gen;
  generator_init(&gen);
  
  MorseSymbol symbols[] = {MORSE_DIT};
  
  // Erstes Senden: erfolgreich
  uint8_t result1 = generator_send_symbols(&gen, symbols, 1);
  assertEquals(0, result1, "Erstes Senden sollte erfolgreich sein");
  
  // Zweites Senden während busy: abgelehnt
  uint8_t result2 = generator_send_symbols(&gen, symbols, 1);
  assertEquals(1, result2, "Zweites Senden sollte abgelehnt werden");
  
  return 0;
}

int test_stop(void)
{
  morse_generator gen;
  generator_init(&gen);
  
  MorseSymbol symbols[] = {MORSE_DAH, MORSE_DAH, MORSE_DAH};
  generator_send_symbols(&gen, symbols, 3);
  
  assertEquals(1, generator_is_busy(&gen), "Should be busy");
  
  generator_stop(&gen);
  
  assertEquals(0, generator_is_busy(&gen), "Should not be busy");
  assertEquals(GEN_STATE_IDLE, gen.state, "State sollte IDLE sein");
  
  return 0;
}

int test_complete_sequence_s(void)
{
  morse_generator gen;
  generator_init(&gen);
  
  // S = DIT DIT DIT
  MorseSymbol symbols[] = {MORSE_DIT, MORSE_DIT, MORSE_DIT};
  generator_send_symbols(&gen, symbols, 3);
  
  // Erwartete Sequenz:
  // DIT(1) PAUSE(1) DIT(1) PAUSE(1) DIT(1) PAUSE_CHAR(3)
  // = 1 + 1 + 1 + 1 + 1 + 3 = 8 Ticks total
  
  uint8_t expected[] = {1, 0, 1, 0, 1, 0, 0, 0};
  
  for (uint8_t i = 0; i < 8; i++)
  {
    uint8_t pin = generator_process_tick(&gen);
    assertEquals(expected[i], pin, "Sequenz sollte stimmen");
  }
  
  assertEquals(GEN_STATE_IDLE, gen.state, "Nach Sequenz: IDLE");
  
  return 0;
}

int test_complete_sequence_o(void)
{
  morse_generator gen;
  generator_init(&gen);
  
  // O = DAH DAH DAH
  MorseSymbol symbols[] = {MORSE_DAH, MORSE_DAH, MORSE_DAH};
  generator_send_symbols(&gen, symbols, 3);
  
  // Erwartete Sequenz:
  // DAH(3) PAUSE(1) DAH(3) PAUSE(1) DAH(3) PAUSE_CHAR(3)
  // = 3 + 1 + 3 + 1 + 3 + 3 = 14 Ticks total
  
  uint8_t expected[] = {1,1,1, 0, 1,1,1, 0, 1,1,1, 0,0,0};
  
  for (uint8_t i = 0; i < 14; i++)
  {
    uint8_t pin = generator_process_tick(&gen);
    assertEquals(expected[i], pin, "Sequenz sollte stimmen");
  }
  
  assertEquals(GEN_STATE_IDLE, gen.state, "Nach Sequenz: IDLE");
  
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
        .name = "Send DIT",
        .testMethod = test_send_dit,
      },
      {
        .name = "DIT Timing",
        .testMethod = test_dit_timing,
      },
      {
        .name = "DAH Timing",
        .testMethod = test_dah_timing,
      },
      {
        .name = "Multiple Symbols",
        .testMethod = test_multiple_symbols,
      },
      {
        .name = "Send Space",
        .testMethod = test_send_space,
      },
      {
        .name = "Busy Reject",
        .testMethod = test_busy_reject,
      },
      {
        .name = "Stop",
        .testMethod = test_stop,
      },
      {
        .name = "Complete Sequence S",
        .testMethod = test_complete_sequence_s,
      },
      {
        .name = "Complete Sequence O",
        .testMethod = test_complete_sequence_o,
      },
    };
    TestSuite suite = {
      .name = "Morse-Generator Tests",
      .testsToRunLength = 10,
      .testsToRun = tests,
    };
    return testerRunSuite(&suite);
  }
  return configErrors;
}

/* Testsammlung: Ende                                                         */
// EOF
