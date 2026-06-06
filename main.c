/*!
  \file main.c
  \brief Hauptprogramm für den Mikrokontroller.
  \author Henrik Lipskoch

  \details Das Hauptprogramm dient der Ausführung auf der Hardware und nicht der
  Simulation.
*/

// Initialisiert und setzt auch die Taktfrequenz.
#include "init.h"

// Betrieb
#include "run.h"

#include <inttypes.h>
#include <avr/io.h>
#include <stdint.h>

/*!
  \brief Initialisiert und startet den Betrieb.

  \details
  - initialisiert durch Aufruf von init()
  - falls keine Fehler (init liefert 0), dann
    + Endlosschleife, die run() aufgeruft

  \return 0 immer
*/
int main(void)
{
  uint8_t init_result = init();
  if (init_result == 0)
  {
    while(1)
    {
      run();
    }
  }
  else
  {
    // TODO
    // reagiere auf Initialisierungsfehler
  }
  return 0;
}

