/*!
  \file modul-ringbuffer-test.c
  \brief Testet den Ringbuffer (ASCII-Version)
*/

#include "modul-ringbuffer.h"
#include <libunittester/unittester.h>
#include <stdio.h>

/*----------------------------------------------------------------------------*/
/* Testfälle: Beginn                                                          */

int test_init(void)
{
  morse_ringbuffer buf;
  ringbuffer_init(&buf);
  
  assertEquals(0, buf.write_pos, "write_pos sollte 0 sein");
  assertEquals(0, buf.read_pos, "read_pos sollte 0 sein");
  assertEquals(0, buf.count, "count sollte 0 sein");
  assertEquals(1, ringbuffer_is_empty(&buf), "Buffer sollte leer sein");
  
  return 0;
}

int test_write_read(void)
{
  morse_ringbuffer buf;
  ringbuffer_init(&buf);
  
  char char_in = 'A';
  char char_out;
  
  // Schreiben
  assertEquals(0, ringbuffer_write(&buf, char_in), "Schreiben sollte klappen");
  assertEquals(1, buf.count, "Count sollte 1 sein");
  
  // Lesen
  assertEquals(0, ringbuffer_read(&buf, &char_out), "Lesen sollte klappen");
  assertEquals(char_in, char_out, "Zeichen sollte gleich sein");
  assertEquals(0, buf.count, "Count sollte wieder 0 sein");
  
  return 0;
}

int test_full(void)
{
  morse_ringbuffer buf;
  ringbuffer_init(&buf);
  
  char c = 'X';
  
  // Fülle Buffer (64 Zeichen)
  for (uint8_t i = 0; i < 64; i++)
  {
    assertEquals(0, ringbuffer_write(&buf, c), "Schreiben sollte klappen");
  }
  
  assertEquals(1, ringbuffer_is_full(&buf), "Buffer sollte voll sein");
  assertEquals(64, buf.count, "Count sollte 64 sein");
  
  // Versuch noch eins zu schreiben
  assertEquals(1, ringbuffer_write(&buf, c), "Schreiben sollte fehlschlagen");
  
  return 0;
}

int test_wrap_around(void)
{
  morse_ringbuffer buf;
  ringbuffer_init(&buf);
  
  char char1 = 'S';
  char char2 = 'O';
  char char_out;
  
  // Fülle und leere mehrmals
  for (uint8_t i = 0; i < 5; i++)
  {
    // Schreibe 10 Zeichen
    for (uint8_t j = 0; j < 10; j++)
    {
      ringbuffer_write(&buf, (j % 2 == 0) ? char1 : char2);
    }
    
    // Lese 10 Zeichen
    for (uint8_t j = 0; j < 10; j++)
    {
      ringbuffer_read(&buf, &char_out);
      char expected = (j % 2 == 0) ? char1 : char2;
      assertEquals(expected, char_out, "Zeichen sollte korrekt sein");
    }
  }
  
  assertEquals(1, ringbuffer_is_empty(&buf), "Buffer sollte leer sein");
  
  return 0;
}

int test_sos(void)
{
  morse_ringbuffer buf;
  ringbuffer_init(&buf);
  
  // Schreibe SOS
  ringbuffer_write(&buf, 'S');
  ringbuffer_write(&buf, 'O');
  ringbuffer_write(&buf, 'S');
  
  assertEquals(3, buf.count, "Count sollte 3 sein");
  
  // Lese SOS
  char c;
  ringbuffer_read(&buf, &c);
  assertEquals('S', c, "Erstes Zeichen sollte S sein");
  
  ringbuffer_read(&buf, &c);
  assertEquals('O', c, "Zweites Zeichen sollte O sein");
  
  ringbuffer_read(&buf, &c);
  assertEquals('S', c, "Drittes Zeichen sollte S sein");
  
  assertEquals(1, ringbuffer_is_empty(&buf), "Buffer sollte leer sein");
  
  return 0;
}

int test_hello_world(void)
{
  morse_ringbuffer buf;
  ringbuffer_init(&buf);
  
  char* message = "HELLO WORLD";
  
  // Schreibe Message
  for (uint8_t i = 0; message[i] != '\0'; i++)
  {
    ringbuffer_write(&buf, message[i]);
  }
  
  assertEquals(11, buf.count, "Count sollte 11 sein (HELLO WORLD)");
  
  // Lese Message zurück
  char result[12];
  for (uint8_t i = 0; i < 11; i++)
  {
    ringbuffer_read(&buf, &result[i]);
  }
  result[11] = '\0';
  
  // Vergleiche String
  for (uint8_t i = 0; i < 11; i++)
  {
    assertEquals(message[i], result[i], "Zeichen sollte übereinstimmen");
  }
  
  return 0;
}

int test_empty_read(void)
{
  morse_ringbuffer buf;
  ringbuffer_init(&buf);
  
  char c;
  
  // Versuch aus leerem Buffer zu lesen
  assertEquals(1, ringbuffer_read(&buf, &c), "Lesen sollte fehlschlagen");
  assertEquals(1, ringbuffer_is_empty(&buf), "Buffer sollte leer sein");
  
  return 0;
}

int test_available(void)
{
  morse_ringbuffer buf;
  ringbuffer_init(&buf);
  
  assertEquals(0, ringbuffer_available(&buf), "Verfügbar sollte 0 sein");
  
  ringbuffer_write(&buf, 'A');
  assertEquals(1, ringbuffer_available(&buf), "Verfügbar sollte 1 sein");
  
  ringbuffer_write(&buf, 'B');
  ringbuffer_write(&buf, 'C');
  assertEquals(3, ringbuffer_available(&buf), "Verfügbar sollte 3 sein");
  
  char c;
  ringbuffer_read(&buf, &c);
  assertEquals(2, ringbuffer_available(&buf), "Verfügbar sollte 2 sein");
  
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
        .name = "Schreiben und Lesen",
        .testMethod = test_write_read,
      },
      {
        .name = "Buffer voll",
        .testMethod = test_full,
      },
      {
        .name = "Wrap-around",
        .testMethod = test_wrap_around,
      },
      {
        .name = "SOS Test",
        .testMethod = test_sos,
      },
      {
        .name = "HELLO WORLD",
        .testMethod = test_hello_world,
      },
      {
        .name = "Lesen aus leerem Buffer",
        .testMethod = test_empty_read,
      },
      {
        .name = "Available Count",
        .testMethod = test_available,
      },
    };
    TestSuite suite = {
      .name = "Ringbuffer-Modul Tests",
      .testsToRunLength = 8,
      .testsToRun = tests,
    };
    return testerRunSuite(&suite);
  }
  return configErrors;
}

/* Testsammlung: Ende                                                         */
// EOF
