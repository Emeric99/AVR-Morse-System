#include "modul-display.h"

/* Modulmethoden / Implementierungen: Beginn                                  */

uint8_t display_init(display_controller* disp)
{
  disp->window[0] = ' ';
  disp->window[1] = ' ';
  disp->window[2] = ' ';
  disp->window[3] = '\0';
  disp->scroll_pos = 0;
  return 0;
}

uint8_t display_set_text(display_controller* disp, const char* text)
{
  uint8_t i;
  
  // Kopiere bis zu 3 Zeichen
  for (i = 0; i < 3 && text[i] != '\0'; i++)
  {
    disp->window[i] = text[i];
  }
  
  // Fülle Rest mit Leerzeichen
  for (; i < 3; i++)
  {
    disp->window[i] = ' ';
  }
  
  disp->window[3] = '\0';
  
  return 0;
}

char* display_get_window(display_controller* disp)
{
  return disp->window;
}

void display_set_scroll_pos(display_controller* disp, uint8_t pos)
{
  disp->scroll_pos = pos;
}

uint8_t display_get_scroll_pos(display_controller* disp)
{
  return disp->scroll_pos;
}

/* Modulmethoden / Implementierungen: Ende                                    */
// EOF
