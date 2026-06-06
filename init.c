#include "init.h"

#include "modul-ringbuffer/modul-ringbuffer-hardware.h"
#include "modul-decoder/modul-decoder-hardware.h"
#include "modul-signal-extractor/modul-signal-extractor-hardware.h"
#include "modul-display/modul-display-hardware.h"
#include "modul-morse-generator/modul-morse-generator-hardware.h"
#include "modul-encoder/modul-encoder-hardware.h"
#include "modul-uart/modul-uart-hardware.h"

// für sei()
#include <avr/interrupt.h>

uint8_t init(void)
{
  uint8_t err_ringbuffer = modul_ringbuffer_init();
  uint8_t err_decoder = modul_decoder_init();
  uint8_t err_signal_extractor = modul_signal_extractor_init();
  uint8_t err_display = modul_display_init();
 uint8_t err_encoder = modul_encoder_init();
 uint8_t err_uart = modul_uart_init();
  uint8_t err_morse_generator = modul_morse_generator_init();
 uint8_t errors = 0;
  if (err_ringbuffer != 0)
  {
    errors += 1;
  }
  if (err_decoder != 0)
  {
    errors += 2;
  }
  if (err_signal_extractor != 0)
  {
    errors += 4;
  }
  if (err_display != 0)
  {
    errors += 8;
  }
  if (err_encoder != 0)
  {
    errors += 16;
  }
  if (err_morse_generator != 0)
  {
    errors += 32;
  }
  if (err_uart !=0)
  {
    errors += 64;
  }
  // DONE Im Interrupt-Betrieb wird nach der Modulinitialisierung hier sei()
  // aufgerufen.
  sei();
  return errors;
}

