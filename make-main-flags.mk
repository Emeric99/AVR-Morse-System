### Compiler-Einstellungen für Make für das Hauptprogramm                     ###

MCU := atmega644p
CC := avr-gcc

# Compiler-Einstellungen: Beginn -----------------------------------------------#
CFLAGS := -mmcu=$(MCU) \
	  -I /usr/include/simavr/ \
	  --all-warnings \
          --extra-warnings \
          -Wpedantic \
	  -O

CFLAGS_DEBUG := $(CFLAGS) \
		-gdwarf

# Compiler-Einstellungen: Ende -------------------------------------------------#
