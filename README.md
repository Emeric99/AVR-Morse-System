# AVR Morse System

Ein eingebettetes System zur Morse-Kodierung und -Dekodierung, entwickelt in C für den **AVR-Mikrocontroller** im Rahmen des Moduls **Eingebettete Systeme** an der Hochschule Bremerhaven.

---

## Systemübersicht

Das System empfängt Text über UART, kodiert ihn in Morse-Signale und gibt diese über einen digitalen Ausgang aus. Gleichzeitig können eingehende Morse-Signale dekodiert und als ASCII-Text über UART ausgegeben werden.

```
Text (UART) → Encoder → Morse-Generator → Signal (AVR-Pin)
Signal (AVR-Pin) → Signal-Extraktor → Decoder → Text (UART)
```

---

## Module

| Modul | Beschreibung |
|-------|-------------|
| `modul-uart` | UART-Kommunikation mit Ringpuffer (TX/RX) |
| `modul-ringbuffer` | Generischer Ringpuffer für Zeichenübertragung |
| `modul-encoder` | Text → Morse-Symbole (Dit/Dah) |
| `modul-decoder` | Morse-Symbole → ASCII (Lookup-Tabelle A–Z, 0–9) |
| `modul-morse-generator` | State Machine zur zeitgesteuerten Signalerzeugung |
| `modul-signal-extractor` | Erkennung von Dit/Dah aus digitalem Eingangssignal |
| `modul-display` | Ausgabe auf Display |

Jedes Modul folgt einer einheitlichen Struktur:

```
modul-XXX/
├── modul-XXX.h              # Schnittstelle (hardware-unabhängig)
├── modul-XXX.c              # Implementierung (hardware-unabhängig)
├── modul-XXX-hardware.h     # Hardware-Abstraktion
├── modul-XXX-hardware.c     # Hardware-Implementierung (AVR-spezifisch)
├── modul-XXX-test.c         # Unit-Tests
└── Makefile
```

---

## Tech-Stack

| Bereich | Technologie |
|--------|-------------|
| Sprache | C (C99) |
| Plattform | AVR-Mikrocontroller |
| Compiler | avr-gcc |
| Simulator | simavr |
| Debugger | avr-gdb / gdb |
| Build-System | GNU Make |

---

## Projektstruktur

```
AVR-Morse-System/
├── main.c                    # Hauptprogramm (Board)
├── main-sim.c                # Hauptprogramm (Simulator)
├── init.c / init.h           # Initialisierung
├── run.c / run.h             # Hauptschleife
├── morse-types.h             # Gemeinsame Typdefinitionen
├── modul-uart/               # UART mit Ringpuffer
├── modul-ringbuffer/         # Generischer Ringpuffer
├── modul-encoder/            # Text → Morse
├── modul-decoder/            # Morse → Text (A–Z, 0–9)
├── modul-morse-generator/    # Signalerzeugung (State Machine)
├── modul-signal-extractor/   # Signalauswertung
├── modul-display/            # Display-Ausgabe
├── Makefile                  # Haupt-Makefile
└── Spezifikation/            # Systemspezifikation (LaTeX/PDF)
```

---

## Build & Ausführung

### Voraussetzungen

```bash
sudo apt install gcc-avr avr-libc make simavr gdb
```

### Mikrokontroller-Programm bauen

```bash
make main.hex
```

### Auf Board übertragen

```bash
make main-firm
```

### Simulation starten

```bash
make main-simulation
```

### Unit-Tests eines Moduls ausführen

```bash
cd modul-decoder
make test
```

### Aufräumen

```bash
make clean
```

---

## Technische Highlights

- **Modulare Architektur** — klare Trennung zwischen hardware-abhängigem und hardware-unabhängigem Code
- **State Machine** im Morse-Generator für präzises Timing (Dit/Dah/Pausen)
- **Lookup-Tabelle** im Decoder für schnelle Morse → ASCII Konvertierung (A–Z, 0–9)
- **Ringpuffer** für UART TX/RX mit Wrap-around
- **Unit-Tests** für alle hardware-unabhängigen Module
- **Simulation** mit `simavr` — kein Board nötig zum Testen

---

## Was ich dabei gelernt habe

- Embedded-Programmierung in C für AVR-Mikrocontroller
- Hardware-Abstraktion und modulare Softwarearchitektur
- Implementierung von State Machines für Echtzeitsysteme
- UART-Kommunikation und Ringpuffer-Datenstrukturen
- Unit-Testing für eingebettete Systeme
- Simulation und Debugging mit simavr und avr-gdb
- Dokumentation mit LaTeX (SRS, SDD, SPMP)

---

*Modul: Eingebettete Systeme · Hochschule Bremerhaven · 2025*
