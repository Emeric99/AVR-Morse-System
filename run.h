/*!
  \file run.h
  \brief Dirigiert die zentrale Abarbeitung des Mikrokontrollers.
  \author Henrik Lipskoch
*/

#ifndef _RUN_H
#define _RUN_H 1

/*!
  \brief Bildet die zentrale Steuerung während des Betriebs

  Die Methode dirigiert die Abarbeitung des Mikrokontrollers, in dem sie die
  run-Methoden der Module startet.
*/
void run(void);

#endif // _RUN_H

