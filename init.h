/*!
  \file init.h
  \brief Initialisiert den Mikrokontroller.
  \author Henrik Lipskoch
*/

#ifndef _INIT_H
#define _INIT_H 1

// Importiere vordefinierte Integer-Datentypen.
// Dies schließt den 8-Bit-Datentyp ein.
#include <inttypes.h>

/*!
  \def F_CPU
  \brief Gibt die Frequenz des Mikrokontrollers an den Quellcode weiter.

  Der Quellcode kann von sich aus nicht wissen, mit welcher Frequenz
  der Kontroller als Hardware später läuft und dieser Parameter
  ermöglicht es, dem Code die Hardwareeinstellung mitzuteilen.
*/
#define F_CPU 16000000UL

/*!
  \brief Initialisiert den Mikrokontroller und initialisiert alle Module.

  \attention Im Interrupt-Betrieb wird nach der Modulinitialisierung hier sei()
  aufgerufen.

  \retval 0  falls ohne Fehler durchgelaufen
  \retval >0 falls unbekannter Fehler aufgetreten
  \retval <0 falls andere Fehler aufgetreten sind
*/
uint8_t init(void);

#endif // _INIT_H

