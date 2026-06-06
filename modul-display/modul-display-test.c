/*!
  \file modul-display-test.c
  \brief Testet den Display-Controller
*/

#include "modul-display.h"
#include <libunittester/unittester.h>
#include <stdio.h>
#include <string.h>

/*----------------------------------------------------------------------------*/
/* Testfälle: Beginn                                                          */

int test_init(void)
{
  display_controller disp;
  display_init(&disp);
  
  assertEquals(0, strcmp(disp.window, "   "), "Window sollte '   ' sein");
  assertEquals(0, disp.scroll_pos, "Scroll-Position sollte 0 sein");
  
  return 0;
}

int test_set_text_full(void)
{
  display_controller disp;
  display_init(&disp);
  
  display_set_text(&disp, "ABC");
  
  assertEquals(0, strcmp(display_get_window(&disp), "ABC"), "Window sollte 'ABC' sein");
  
  return 0;
}

int test_set_text_short(void)
{
  display_controller disp;
  display_init(&disp);
  
  display_set_text(&disp, "HI");
  
  assertEquals(0, strcmp(display_get_window(&disp), "HI "), "Window sollte 'HI ' sein");
  
  return 0;
}

int test_set_text_empty(void)
{
  display_controller disp;
  display_init(&disp);
  
  display_set_text(&disp, "");
  
  assertEquals(0, strcmp(display_get_window(&disp), "   "), "Window sollte '   ' sein");
  
  return 0;
}

int test_set_text_long(void)
{
  display_controller disp;
  display_init(&disp);
  
  // Text länger als 3 Zeichen - nur erste 3 nehmen
  display_set_text(&disp, "HELLO");
  
  assertEquals(0, strcmp(display_get_window(&disp), "HEL"), "Window sollte 'HEL' sein");
  
  return 0;
}

int test_scroll_pos(void)
{
  display_controller disp;
  display_init(&disp);
  
  display_set_scroll_pos(&disp, 5);
  assertEquals(5, display_get_scroll_pos(&disp), "Scroll-Position sollte 5 sein");
  
  display_set_scroll_pos(&disp, 10);
  assertEquals(10, display_get_scroll_pos(&disp), "Scroll-Position sollte 10 sein");
  
  return 0;
}

int test_multiple_updates(void)
{
  display_controller disp;
  display_init(&disp);
  
  // Erste Anzeige
  display_set_text(&disp, "ABC");
  assertEquals(0, strcmp(display_get_window(&disp), "ABC"), "Window sollte 'ABC' sein");
  
  // Zweite Anzeige
  display_set_text(&disp, "XYZ");
  assertEquals(0, strcmp(display_get_window(&disp), "XYZ"), "Window sollte 'XYZ' sein");
  
  // Dritte Anzeige (kürzer)
  display_set_text(&disp, "OK");
  assertEquals(0, strcmp(display_get_window(&disp), "OK "), "Window sollte 'OK ' sein");
  
  return 0;
}

int test_with_digits(void)
{
  display_controller disp;
  display_init(&disp);
  
  display_set_text(&disp, "123");
  
  assertEquals(0, strcmp(display_get_window(&disp), "123"), "Window sollte '123' sein");
  
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
        .name = "Text setzen (3 Zeichen)",
        .testMethod = test_set_text_full,
      },
      {
        .name = "Text setzen (kurz)",
        .testMethod = test_set_text_short,
      },
      {
        .name = "Text setzen (leer)",
        .testMethod = test_set_text_empty,
      },
      {
        .name = "Text setzen (zu lang)",
        .testMethod = test_set_text_long,
      },
      {
        .name = "Scroll-Position",
        .testMethod = test_scroll_pos,
      },
      {
        .name = "Mehrere Updates",
        .testMethod = test_multiple_updates,
      },
      {
        .name = "Mit Zahlen",
        .testMethod = test_with_digits,
      },
    };
    TestSuite suite = {
      .name = "Display-Modul Tests",
      .testsToRunLength = 8,
      .testsToRun = tests,
    };
    return testerRunSuite(&suite);
  }
  return configErrors;
}

/* Main: Ende                                                                 */
// EOF
