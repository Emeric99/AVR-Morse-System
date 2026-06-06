/*!
  \file modul-ringbuffer.h
  \brief Hardware-unabhängige Definitionen für Ringbuffer
 
  \details Ringbuffer für ASCII-Zeichen (Morse-Code Ausgabe)

  \author Dein Team
*/

#ifndef _MODUL_RINGBUFFER_H
#define _MODUL_RINGBUFFER_H 1

/* Importe: Beginn                                                            */
#include <inttypes.h>
/* Importe: Ende                                                              */

/*----------------------------------------------------------------------------*/
/* Datenstrukturen: Beginn                                                    */

/*!
  \brief Ringbuffer Kapazität
*/
typedef enum {
  RINGBUFFER_CAPACITY = 64
} RingbufferSize;

/*!
  \brief Ringbuffer für ASCII-Zeichen
*/
typedef struct morse_ringbuffer
{
  char data[64];        // ASCII-Zeichen (64 Zeichen Kapazität)
  uint8_t write_pos;    // Schreib-Position (0-63)
  uint8_t read_pos;     // Lese-Position (0-63)
  uint8_t count;        // Anzahl gespeicherter Zeichen (0-64)
} morse_ringbuffer;

/* Datenstrukturen: Ende                                                      */
/*----------------------------------------------------------------------------*/
/* Modulmethoden / Definitionen: Beginn                                       */

/*!
  \brief Initialisiert den Ringbuffer
  
  \param buf Zeiger auf Ringbuffer-Struktur
  \return 0 bei Erfolg
*/
uint8_t ringbuffer_init(morse_ringbuffer* buf);

/*!
  \brief Schreibt ein ASCII-Zeichen in den Buffer
  
  \param buf Zeiger auf Ringbuffer-Struktur
  \param character ASCII-Zeichen ('A'-'Z', '0'-'9', ' ')
  \return 0 bei Erfolg, 1 wenn Buffer voll
*/
uint8_t ringbuffer_write(morse_ringbuffer* buf, char character);

/*!
  \brief Liest ein ASCII-Zeichen aus dem Buffer
  
  \param buf Zeiger auf Ringbuffer-Struktur
  \param character Zeiger für Ausgabe-Zeichen
  \return 0 bei Erfolg, 1 wenn Buffer leer
*/
uint8_t ringbuffer_read(morse_ringbuffer* buf, char* character);

/*!
  \brief Gibt Anzahl gespeicherter Zeichen zurück
  
  \param buf Zeiger auf Ringbuffer-Struktur
  \return Anzahl Zeichen im Buffer (0-64)
*/
uint8_t ringbuffer_available(morse_ringbuffer* buf);

/*!
  \brief Prüft ob Buffer voll ist
  
  \param buf Zeiger auf Ringbuffer-Struktur
  \return 1 wenn voll, 0 sonst
*/
uint8_t ringbuffer_is_full(morse_ringbuffer* buf);

/*!
  \brief Prüft ob Buffer leer ist
  
  \param buf Zeiger auf Ringbuffer-Struktur
  \return 1 wenn leer, 0 sonst
*/
uint8_t ringbuffer_is_empty(morse_ringbuffer* buf);

/* Modulmethoden / Definitionen: Ende                                         */
#endif // _MODUL_RINGBUFFER_H
