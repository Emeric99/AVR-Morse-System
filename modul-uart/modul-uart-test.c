/*!
  \file modul-uart-test.c
  \brief Testet das UART-Modul
*/

#include "modul-uart.h"
#include <libunittester/unittester.h>
#include <stdio.h>

/*----------------------------------------------------------------------------*/
/* Testfälle: Beginn                                                          */

int test_tx_buffer_init(void)
{
  uart_tx_buffer tx;
  uart_tx_init(&tx);
  
  assertEquals(0, tx.head, "Head sollte 0 sein");
  assertEquals(0, tx.tail, "Tail sollte 0 sein");
  assertEquals(0, tx.count, "Count sollte 0 sein");
  assertEquals(1, uart_tx_is_empty(&tx), "Buffer sollte leer sein");
  
  return 0;
}

int test_rx_buffer_init(void)
{
  uart_rx_buffer rx;
  uart_rx_init(&rx);
  
  assertEquals(0, rx.head, "Head sollte 0 sein");
  assertEquals(0, rx.tail, "Tail sollte 0 sein");
  assertEquals(0, rx.count, "Count sollte 0 sein");
  assertEquals(1, uart_rx_is_empty(&rx), "Buffer sollte leer sein");
  
  return 0;
}

int test_tx_put_get(void)
{
  uart_tx_buffer tx;
  uart_tx_init(&tx);
  
  uint8_t result = uart_tx_put(&tx, 'A');
  assertEquals(0, result, "Put sollte erfolgreich sein");
  assertEquals(1, tx.count, "Count sollte 1 sein");
  assertEquals(0, uart_tx_is_empty(&tx), "Buffer sollte nicht leer sein");
  
  uint8_t data;
  result = uart_tx_get(&tx, &data);
  assertEquals(0, result, "Get sollte erfolgreich sein");
  assertEquals('A', data, "Daten sollten 'A' sein");
  assertEquals(0, tx.count, "Count sollte 0 sein");
  assertEquals(1, uart_tx_is_empty(&tx), "Buffer sollte leer sein");
  
  return 0;
}

int test_rx_put_get(void)
{
  uart_rx_buffer rx;
  uart_rx_init(&rx);
  
  uint8_t result = uart_rx_put(&rx, 'B');
  assertEquals(0, result, "Put sollte erfolgreich sein");
  assertEquals(1, rx.count, "Count sollte 1 sein");
  
  uint8_t data;
  result = uart_rx_get(&rx, &data);
  assertEquals(0, result, "Get sollte erfolgreich sein");
  assertEquals('B', data, "Daten sollten 'B' sein");
  
  return 0;
}



int test_tx_get_empty(void)
{
  uart_tx_buffer tx;
  uart_tx_init(&tx);
  
  uint8_t data;
  uint8_t result = uart_tx_get(&tx, &data);
  
  assertEquals(1, result, "Get sollte fehlschlagen (Buffer leer)");
  
  return 0;
}

int test_rx_get_empty(void)
{
  uart_rx_buffer rx;
  uart_rx_init(&rx);
  
  uint8_t data;
  uint8_t result = uart_rx_get(&rx, &data);
  
  assertEquals(1, result, "Get sollte fehlschlagen (Buffer leer)");
  
  return 0;
}

int test_tx_circular(void)
{
  uart_tx_buffer tx;
  uart_tx_init(&tx);
  
  /* Füge 3 Bytes ein */
  uart_tx_put(&tx, 'A');
  uart_tx_put(&tx, 'B');
  uart_tx_put(&tx, 'C');
  
  /* Hole 2 Bytes */
  uint8_t data;
  uart_tx_get(&tx, &data);
  assertEquals('A', data, "Erstes Byte sollte 'A' sein");
  uart_tx_get(&tx, &data);
  assertEquals('B', data, "Zweites Byte sollte 'B' sein");
  
  /* Füge 2 neue Bytes ein */
  uart_tx_put(&tx, 'D');
  uart_tx_put(&tx, 'E');
  
  /* Hole alle */
  uart_tx_get(&tx, &data);
  assertEquals('C', data, "Drittes Byte sollte 'C' sein");
  uart_tx_get(&tx, &data);
  assertEquals('D', data, "Viertes Byte sollte 'D' sein");
  uart_tx_get(&tx, &data);
  assertEquals('E', data, "Fünftes Byte sollte 'E' sein");
  
  assertEquals(1, uart_tx_is_empty(&tx), "Buffer sollte leer sein");
  
  return 0;
}

int test_rx_circular(void)
{
  uart_rx_buffer rx;
  uart_rx_init(&rx);
  
  /* Test circular buffer wrap-around */
  uart_rx_put(&rx, 'X');
  uart_rx_put(&rx, 'Y');
  uart_rx_put(&rx, 'Z');
  
  uint8_t data;
  uart_rx_get(&rx, &data);
  assertEquals('X', data, "Sollte 'X' sein");
  
  uart_rx_put(&rx, 'W');
  
  uart_rx_get(&rx, &data);
  assertEquals('Y', data, "Sollte 'Y' sein");
  uart_rx_get(&rx, &data);
  assertEquals('Z', data, "Sollte 'Z' sein");
  uart_rx_get(&rx, &data);
  assertEquals('W', data, "Sollte 'W' sein");
  
  return 0;
}

int test_tx_count(void)
{
  uart_tx_buffer tx;
  uart_tx_init(&tx);
  
  assertEquals(0, uart_tx_count(&tx), "Count sollte 0 sein");
  
  uart_tx_put(&tx, 'A');
  assertEquals(1, uart_tx_count(&tx), "Count sollte 1 sein");
  
  uart_tx_put(&tx, 'B');
  uart_tx_put(&tx, 'C');
  assertEquals(3, uart_tx_count(&tx), "Count sollte 3 sein");
  
  uint8_t data;
  uart_tx_get(&tx, &data);
  assertEquals(2, uart_tx_count(&tx), "Count sollte 2 sein");
  
  return 0;
}

int test_rx_count(void)
{
  uart_rx_buffer rx;
  uart_rx_init(&rx);
  
  assertEquals(0, uart_rx_count(&rx), "Count sollte 0 sein");
  
  uart_rx_put(&rx, 'A');
  assertEquals(1, uart_rx_count(&rx), "Count sollte 1 sein");
  
  uart_rx_put(&rx, 'B');
  uart_rx_put(&rx, 'C');
  assertEquals(3, uart_rx_count(&rx), "Count sollte 3 sein");
  
  uint8_t data;
  uart_rx_get(&rx, &data);
  assertEquals(2, uart_rx_count(&rx), "Count sollte 2 sein");
  
  return 0;
}

/* Testfälle: Ende                                                            */
/*----------------------------------------------------------------------------*/
/* Testsammlung: Beginn                                                       */

int main(int argc, char** argv)
{
  int configErrors = testerConfigure(argc, argv);
  if (!configErrors)
  {
    CommonTest tests[] = {
      {
        .name = "TX Buffer Init",
        .testMethod = test_tx_buffer_init,
      },
      {
        .name = "RX Buffer Init",
        .testMethod = test_rx_buffer_init,
      },
      {
        .name = "TX Put/Get",
        .testMethod = test_tx_put_get,
      },
      {
        .name = "RX Put/Get",
        .testMethod = test_rx_put_get,
      },
      {
        .name = "TX Get Empty",
        .testMethod = test_tx_get_empty,
      },
      {
        .name = "RX Get Empty",
        .testMethod = test_rx_get_empty,
      },
      {
        .name = "TX Circular",
        .testMethod = test_tx_circular,
      },
      {
        .name = "RX Circular",
        .testMethod = test_rx_circular,
      },
      {
        .name = "TX Count",
        .testMethod = test_tx_count,
      },
      {
        .name = "RX Count",
        .testMethod = test_rx_count,
      },
    };
    TestSuite suite = {
      .name = "UART Tests",
      .testsToRunLength = 10,
      .testsToRun = tests,
    };
    return testerRunSuite(&suite);
  }
  return configErrors;
}

/* Testsammlung: Ende                                                         */
// EOF
