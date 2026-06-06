#include "modul-ringbuffer.h"

/* Modulmethoden / Implementierungen: Beginn                                  */

uint8_t ringbuffer_init(morse_ringbuffer* buf)
{
  buf->write_pos = 0;
  buf->read_pos = 0;
  buf->count = 0;
  return 0;
}

uint8_t ringbuffer_write(morse_ringbuffer* buf, char character)
{
  // Prüfe ob voll
  if (buf->count >= RINGBUFFER_CAPACITY)
  {
    return 1; // Fehler: Buffer voll
  }

  // Schreibe Zeichen
  buf->data[buf->write_pos] = character;

  // Update write_pos (mit Wrap-around)
  buf->write_pos = (buf->write_pos + 1) % RINGBUFFER_CAPACITY;

  // Erhöhe count
  buf->count++;

  return 0; // Erfolg
}

uint8_t ringbuffer_read(morse_ringbuffer* buf, char* character)
{
  // Prüfe ob leer
  if (buf->count == 0)
  {
    return 1; // Fehler: Buffer leer
  }

  // Lese Zeichen
  *character = buf->data[buf->read_pos];

  // Update read_pos (mit Wrap-around)
  buf->read_pos = (buf->read_pos + 1) % RINGBUFFER_CAPACITY;

  // Verringere count
  buf->count--;

  return 0; // Erfolg
}

uint8_t ringbuffer_available(morse_ringbuffer* buf)
{
  return buf->count;
}

uint8_t ringbuffer_is_full(morse_ringbuffer* buf)
{
  return (buf->count >= RINGBUFFER_CAPACITY) ? 1 : 0;
}

uint8_t ringbuffer_is_empty(morse_ringbuffer* buf)
{
  return (buf->count == 0) ? 1 : 0;
}

/* Modulmethoden / Implementierungen: Ende                                    */
// EOF
