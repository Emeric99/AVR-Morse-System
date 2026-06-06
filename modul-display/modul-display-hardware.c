#include "modul-display-hardware.h"
#include <avr/io.h>
#include <avr/interrupt.h>

/*----------------------------------------------------------------------------*/
/* Hardware-Konfiguration                       */

typedef enum {
  DISPLAY_DIGIT_1 = 0,
  DISPLAY_DIGIT_2 = 1,
  DISPLAY_DIGIT_3 = 2,
  DISPLAY_DIGIT_COUNT = 3
} DisplayDigit;

/*----------------------------------------------------------------------------*/
/* Lookup-Tabelle für 7-Segment-Codierung                                    */

// 7-Segment Layout:
//     a
//   f   b
//     g
//   e   c
//     d   (dp)

static const uint8_t segment_codes[] = {
  // Zahlen 0-9
  0b00111111,  // 0: abcdef
  0b00000110,  // 1: bc
  0b01011011,  // 2: abdeg
  0b01001111,  // 3: abcdg
  0b01100110,  // 4: bcfg
  0b01101101,  // 5: acdfg
  0b01111101,  // 6: acdefg
  0b00000111,  // 7: abc
  0b01111111,  // 8: abcdefg
  0b01101111,  // 9: abcdfg
};

/*----------------------------------------------------------------------------*/
/* Globale Display-Controller Instanz                                        */

static display_controller display;
static uint8_t current_digit = 0;

/*----------------------------------------------------------------------------*/
/* Modulmethoden / Implementierungen: Beginn                                 */

uint8_t modul_display_init(void)
{
  /* Initialisiere Display Controller */
  display_init(&display);
  
  /* Konfiguriere PORTB als Ausgang für Segmente (a-g + dp) */
  DDRB = 0xFF;
  PORTB = 0x00;  /* Alle Segmente aus */
  
  /* Konfiguriere PORTD.0, PORTD.1, PORTD.2 als Ausgänge für Digit-Selektion */
  DDRD |= (1 << DDD0) | (1 << DDD1) | (1 << DDD2);
  PORTD &= ~((1 << PORTD0) | (1 << PORTD1) | (1 << PORTD2));  /* Alle Digits aus */
  
  /* Timer0 für Multiplexing konfigurieren (ca. 200Hz = 5ms pro Digit) */
  /* Timer0 CTC Mode, Prescaler 1024 */
  TCCR0A = (1 << WGM01);  /* CTC Mode */
  TCCR0B = (1 << CS02) | (1 << CS00);  /* Prescaler 1024 */
  OCR0A = 77;  /* 16MHz / 1024 / 200Hz - 1 ≈ 77 */
  TIMSK0 = (1 << OCIE0A);  /* Enable Timer0 Compare Interrupt */
  
  return 0;
}

uint8_t modul_display_run(void)
{
  /* Multiplexing läuft im Timer-ISR */
  return 0;
}

static uint8_t char_to_segment_code(char c)
{
  if (c >= '0' && c <= '9')
  {
    return segment_codes[c - '0'];
  }
  else if (c >= 'A' && c <= 'Z')
  {
    /* Vereinfachte Zuordnung - nur ausgewählte Buchstaben */
    switch(c)
    {
      case 'A': return 0b01110111;
      case 'B': return 0b01111100;
      case 'C': return 0b00111001;
      case 'D': return 0b01011110;
      case 'E': return 0b01111001;
      case 'F': return 0b01110001;
      case 'G': return 0b00111101;
      case 'H': return 0b01110110;
      case 'I': return 0b00000110;
      case 'J': return 0b00001110;
      case 'L': return 0b00111000;
      case 'N': return 0b01010100;
      case 'O': return 0b00111111;
      case 'P': return 0b01110011;
      case 'R': return 0b01010000;
      case 'S': return 0b01101101;
      case 'T': return 0b01111000;
      case 'U': return 0b00111110;
      case 'Y': return 0b01101110;
      default: return 0b00000000; /* Leerzeichen */
    }
  }
  else if (c >= 'a' && c <= 'z')
  {
    /* Kleinbuchstaben -> Großbuchstaben */
    return char_to_segment_code(c - 32);
  }
  else if (c == ' ')
  {
    return 0b00000000;
  }
  else if (c == '-')
  {
    return 0b01000000;
  }
  else if (c == '.')
  {
    return 0b10000000;
  }

  return 0b00000000; /* Default: Leerzeichen */
}

uint8_t display_hardware_show(display_controller* disp)
{
  /* Schalte alle Digits aus */
  PORTD &= ~((1 << PORTD0) | (1 << PORTD1) | (1 << PORTD2));
  
  /* Setze Segmente für aktuelles Digit */
  uint8_t code = char_to_segment_code(disp->window[current_digit]);
  PORTB = code;
  
  /* Schalte aktuelles Digit ein */
  switch(current_digit)
  {
    case DISPLAY_DIGIT_1:
      PORTD |= (1 << PORTD0);
      break;
    case DISPLAY_DIGIT_2:
      PORTD |= (1 << PORTD1);
      break;
    case DISPLAY_DIGIT_3:
      PORTD |= (1 << PORTD2);
      break;
  }
  
  /* Nächstes Digit */
  current_digit = (current_digit + 1) % DISPLAY_DIGIT_COUNT;
  
  return 0;
}

void display_hardware_update(display_controller* disp)
{
  /* Wird nicht verwendet - Multiplexing läuft im Timer-ISR */
  (void)disp;
}


/* Timer0 Compare Interrupt - wird ca. alle 5ms aufgerufen */
ISR(TIMER0_COMPA_vect)
{
  /* Multiplexing: Zeige aktuelles Digit */
  display_hardware_show(&display);
}

/* Modulmethoden / Implementierungen: Ende                                    */
// EOF
