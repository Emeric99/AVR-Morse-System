#include "init.h"
#include "run.h"
#include <inttypes.h>
#include "modul-ringbuffer/modul-ringbuffer-hardware.h"
#include "modul-decoder/modul-decoder-hardware.h"
#include "modul-signal-extractor/modul-signal-extractor-hardware.h"
#include "modul-display/modul-display-hardware.h"
#include "modul-encoder/modul-encoder-hardware.h"
#include "modul-morse-generator/modul-morse-generator-hardware.h"
#include "modul-uart/modul-uart-hardware.h"

/* 
 * Instance globale du générateur Morse
 * Définie dans modul-morse-generator-hardware.c
 */
extern morse_generator morse_gen;


void run(void)
{
  /* Exécution des modules */
  modul_ringbuffer_run();
  modul_decoder_run();
  modul_signal_extractor_run();
  modul_display_run();
  modul_encoder_run();
  modul_morse_generator_run();
  modul_uart_run();
  
  /* Logique PC → Morse */
  uint8_t received_char;
  
  /* Vérifie si un caractère est reçu via UART */
  if (uart_receive_byte(&received_char) == 0)
  {
    /* Ignore CR/LF */
    if (received_char == '\r' || received_char == '\n') {
      return;
    }
    
    /* Echo vers PC */
    uart_send_byte(received_char);
    uart_send_string(" -> ");
    
    /* Vérifie si le caractère est supporté */
    if (encoder_is_supported(received_char))
    {
      /* Encode en Morse */
      MorseSymbol symbols[5];
      uint8_t length;
      
      if (encoder_encode_char(received_char, symbols, &length) == 0)
      {
        /* Génère signal Morse - CORRECTION: 3 arguments! */
        if (generator_send_symbols(&morse_gen, symbols, length) == 0)
        {
          uart_send_string("Morse OK\r\n");
        }
        else
        {
          uart_send_string("Generator busy\r\n");
        }
      }
      else
      {
        uart_send_string("Encoding error\r\n");
      }
    }
    else
    {
      uart_send_string("Not supported\r\n");
    }
  }
}
