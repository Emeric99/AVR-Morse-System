/*!
  \file modul-uart-hardware.h
  \brief Hardware-abhängige Definitionen für UART

  \details UART Hardware-Interface für ATmega644PA
  
  Team: es2025_24 (Mittwochsteam)
  
  \author Emeric Tcholagheu
  \author Joyce Sonkwe
*/

#ifndef _MODUL_UART_HARDWARE_H
#define _MODUL_UART_HARDWARE_H 1

/* Importe: Beginn                                                            */

// hardware-unabhängiger Code
#include "modul-uart.h"
// für uint8_t
#include <inttypes.h>

/* Importe: Ende                                                              */
/*----------------------------------------------------------------------------*/
/* Modulmethoden / Definitionen: Beginn                                       */

/*!
  \brief Initialisiert das UART-Modul
  
  \details Konfiguriert USART0:
  - 9600 Baud
  - 8 Data Bits
  - Ungerade Parität (ODD)
  - 2 Stop Bits
  - RX/TX Interrupts aktiviert

  \return möglicher Fehlercode
  \retval 0 kein Fehler
*/
uint8_t modul_uart_init(void);

/*!
  \brief Betreibt das Modul
  
  \details Wird von run() aufgerufen

  \return möglicher Fehlercode
  \retval 0 kein Fehler
*/
uint8_t modul_uart_run(void);

/*!
  \brief Sendet ein einzelnes Byte
  
  \param data Zu sendendes Byte
  \return 0 bei Erfolg, 1 wenn TX-Buffer voll
*/
uint8_t uart_send_byte(uint8_t data);

/*!
  \brief Sendet einen String
  
  \param str Null-terminierter String
  \return 0 bei Erfolg
*/
uint8_t uart_send_string(const char* str);

/*!
  \brief Empfängt ein Byte (nicht-blockierend)
  
  \param data Zeiger für empfangenes Byte
  \return 0 wenn Byte empfangen, 1 wenn RX-Buffer leer
*/
uint8_t uart_receive_byte(uint8_t* data);

/*!
  \brief Prüft ob Daten zum Empfangen vorhanden sind
  
  \return Anzahl verfügbarer Bytes
*/
uint8_t uart_available(void);

/* Modulmethoden / Definitionen: Ende                                         */
#endif // _MODUL_UART_HARDWARE_H
