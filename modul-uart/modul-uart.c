#include "modul-uart.h"

/* Modulmethoden / Implementierungen: Beginn                                  */

uint8_t uart_tx_init(uart_tx_buffer* tx)
{
  tx->head = 0;
  tx->tail = 0;
  tx->count = 0;
  return 0;
}

uint8_t uart_rx_init(uart_rx_buffer* rx)
{
  rx->head = 0;
  rx->tail = 0;
  rx->count = 0;
  return 0;
}

uint8_t uart_tx_put(uart_tx_buffer* tx, uint8_t data)
{
  // Prüfe ob Buffer voll
  if (tx->count >= UART_TX_BUFFER_SIZE)
  {
    return 1; // Buffer voll
  }
  
  // Füge Byte ein
  tx->buffer[tx->head] = data;
  tx->head = (tx->head + 1) % UART_TX_BUFFER_SIZE;
  tx->count++;
  
  return 0; // Erfolg
}

uint8_t uart_tx_get(uart_tx_buffer* tx, uint8_t* data)
{
  // Prüfe ob Buffer leer
  if (tx->count == 0)
  {
    return 1; // Buffer leer
  }
  
  // Hole Byte
  *data = tx->buffer[tx->tail];
  tx->tail = (tx->tail + 1) % UART_TX_BUFFER_SIZE;
  tx->count--;
  
  return 0; // Erfolg
}

uint8_t uart_rx_put(uart_rx_buffer* rx, uint8_t data)
{
  // Prüfe ob Buffer voll
  if (rx->count >= UART_RX_BUFFER_SIZE)
  {
    return 1; // Buffer voll
  }
  
  // Füge Byte ein
  rx->buffer[rx->head] = data;
  rx->head = (rx->head + 1) % UART_RX_BUFFER_SIZE;
  rx->count++;
  
  return 0; // Erfolg
}

uint8_t uart_rx_get(uart_rx_buffer* rx, uint8_t* data)
{
  // Prüfe ob Buffer leer
  if (rx->count == 0)
  {
    return 1; // Buffer leer
  }
  
  // Hole Byte
  *data = rx->buffer[rx->tail];
  rx->tail = (rx->tail + 1) % UART_RX_BUFFER_SIZE;
  rx->count--;
  
  return 0; // Erfolg
}

uint8_t uart_tx_is_empty(uart_tx_buffer* tx)
{
  return (tx->count == 0) ? 1 : 0;
}

uint8_t uart_rx_is_empty(uart_rx_buffer* rx)
{
  return (rx->count == 0) ? 1 : 0;
}

uint8_t uart_tx_count(uart_tx_buffer* tx)
{
  return tx->count;
}

uint8_t uart_rx_count(uart_rx_buffer* rx)
{
  return rx->count;
}

/* Modulmethoden / Implementierungen: Ende                                    */
// EOF
