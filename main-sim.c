/*!
  \file main-sim.c
  \brief Hauptprogramm für die Simulations des Mikrokontrollers.
  \author Henrik Lipskoch

  \details Das Hauptprogramm dient der Ausführung im Simulator und nicht auf
  der Hardware. Es weicht nur wenig vom Hauptprogramm für die Hardware ab und
  definiert hauptsächlich Makros, die für den Simulatorbetrieb wichtig sind.
*/

// Initialisiert und setzt auch die Taktfrequenz.
#include "init.h"

// Betrieb
#include "run.h"

#include <inttypes.h>
#include <avr/io.h>
#include <stdint.h>

#include <avr/avr_mcu_section.h>

// Importe für den Simulator.
#include <sim_vcd_file.h>

// Importiert die Stopp-Funktion, um den Prozessor anzuhalten (sleep_cpu())
#include <avr/sleep.h>

/*!
  \def AVR_MCU
  \brief Definiert den AVR-Typ für den Simulator.
*/
AVR_MCU(F_CPU, "atmega644p");

/*!
  \def AVR_MCU_VCD_FILE
  \brief Definiert die Simulatorausgabedatei und die Dauer der Simulation in
  Mikrosekunden.

  Je nach Version des Simulators funktioniert es nicht, die Dauer hier anzugeben
  und stattdessen läuft der Simulator einfach weniger lange oder länger.
*/
AVR_MCU_VCD_FILE("test-output.vcd", 10000);

/*!
  \brief Definiert die durch den Simulator auszugebenden Register.

  Es bietet sich hier an, Ouput-Ports einzutragen, um die Signale, die der
  Kontroller nach außen sendet zu protokollieren.
*/
const struct avr_mmcu_vcd_trace_t _mytrace[] _MMCU_ = {
  // protokolliere PORTD
  { AVR_MCU_VCD_SYMBOL("PORT_D"), .what = (void*)&PORTD, },
  { AVR_MCU_VCD_SYMBOL("PORT_B"), .what = (void*)&PORTB, },
};


/*!
  \brief Initialisiert und startet den Betrieb.

  \details
  - initialisiert durch Aufruf von init()
  - falls keine Fehler (init liefert 0), dann
    + Endlosschleife, die run() aufgeruft
    + und im Anschluss an run sleep_cpu() aufruft
  - falls Fehler, dann
    + ruft der Code direkt sleep_cpu() auf

  Der Aufruf von sleep_cpu() ist das Signal an den Simulator, die Simulation zu
  stoppen.

  \return 0 immer
 */
int main(void)
{
  uint8_t init_result = init();
  if (init_result == 0)
  {
    // Lege die Simulationsdauer auf 255*255*8 Durchläufe von run() fest
    // Das entspricht bei 16 MHz Taktfrequenz einer Dauer von (fast) 1 s, wenn
    // man je Schleifendurchlauf 4 Takte und für run() 8 Takte benötigt.
    for (uint8_t sim_i = 0; sim_i < 255; sim_i++)
    {
      for (uint8_t sim_j = 0; sim_j < 255; sim_j++)
      {
        for (;;)
        {
          run();
        }
      }
    }
  }
  else
  {
    // TODO
    // reagiere auf Initialisierungsfehler
  }
  // Legt den Prozessor schlafen. D.h. diese Anweisung stoppt
  // ebenfalls den Simulator.
  sleep_cpu();
  return 0;
}

