/*!
  \file modul-uart.h
  \brief Hardware-unabhängige Definitionen für UART-Kommunikation
 
  \details UART-Modul für serielle Kommunikation mit Laborrechner
  
  Konfiguration:
  - 9600 Baud
  - 8 Data Bits
  - Ungerade Parität (Mittwochsteam)
  - 2 Stop Bits

  \author Emeric Tcholagheu
  \author Joyce Sonkwe
*/

#ifndef _MODUL_UART_H
#define _MODUL_UART_H 1

/* Importe: Beginn                                                            */
#include <inttypes.h>
/* Importe: Ende                                                              */

/*----------------------------------------------------------------------------*/
/* Datenstrukturen: Beginn                                                    */

/*!
  \brief UART Buffer-Größe
*/
typedef enum {
  UART_TX_BUFFER_SIZE = 64,
  UART_RX_BUFFER_SIZE = 64
} UARTBufferSize;

/*!
  \brief UART Ringbuffer für TX
*/
typedef struct {
  uint8_t buffer[64];
  uint8_t head;
  uint8_t tail;
  uint8_t count;
} uart_tx_buffer;

/*!
  \brief UART Ringbuffer für RX
*/
typedef struct {
  uint8_t buffer[64];
  uint8_t head;
  uint8_t tail;
  uint8_t count;
} uart_rx_buffer;

/* Datenstrukturen: Ende                                                      */
/*----------------------------------------------------------------------------*/
/* Modulmethoden / Definitionen: Beginn                                       */

/*!
  \brief Initialisiert UART TX Buffer
  
  \param tx Zeiger auf TX-Buffer
  \return 0 bei Erfolg
*/
uint8_t uart_tx_init(uart_tx_buffer* tx);

/*!
  \brief Initialisiert UART RX Buffer
  
  \param rx Zeiger auf RX-Buffer
  \return 0 bei Erfolg
*/
uint8_t uart_rx_init(uart_rx_buffer* rx);

/*!
  \brief Fügt ein Byte in den TX-Buffer ein
  
  \param tx Zeiger auf TX-Buffer
  \param data Zu sendendes Byte
  \return 0 bei Erfolg, 1 wenn Buffer voll
*/
uint8_t uart_tx_put(uart_tx_buffer* tx, uint8_t data);

/*!
  \brief Holt ein Byte aus dem TX-Buffer
  
  \param tx Zeiger auf TX-Buffer
  \param data Zeiger für gelesenes Byte
  \return 0 bei Erfolg, 1 wenn Buffer leer
*/
uint8_t uart_tx_get(uart_tx_buffer* tx, uint8_t* data);

/*!
  \brief Fügt ein Byte in den RX-Buffer ein
  
  \param rx Zeiger auf RX-Buffer
  \param data Empfangenes Byte
  \return 0 bei Erfolg, 1 wenn Buffer voll
*/
uint8_t uart_rx_put(uart_rx_buffer* rx, uint8_t data);

/*!
  \brief Holt ein Byte aus dem RX-Buffer
  
  \param rx Zeiger auf RX-Buffer
  \param data Zeiger für gelesenes Byte
  \return 0 bei Erfolg, 1 wenn Buffer leer
*/
uint8_t uart_rx_get(uart_rx_buffer* rx, uint8_t* data);

/*!
  \brief Prüft ob TX-Buffer leer ist
  
  \param tx Zeiger auf TX-Buffer
  \return 1 wenn leer, 0 sonst
*/
uint8_t uart_tx_is_empty(uart_tx_buffer* tx);

/*!
  \brief Prüft ob RX-Buffer leer ist
  
  \param rx Zeiger auf RX-Buffer
  \return 1 wenn leer, 0 sonst
*/
uint8_t uart_rx_is_empty(uart_rx_buffer* rx);

/*!
  \brief Gibt Anzahl Bytes im TX-Buffer zurück
  
  \param tx Zeiger auf TX-Buffer
  \return Anzahl Bytes
*/
uint8_t uart_tx_count(uart_tx_buffer* tx);

/*!
  \brief Gibt Anzahl Bytes im RX-Buffer zurück
  
  \param rx Zeiger auf RX-Buffer
  \return Anzahl Bytes
*/
uint8_t uart_rx_count(uart_rx_buffer* rx);

/* Modulmethoden / Definitionen: Ende                                         */
#endif // _MODUL_UART_H
