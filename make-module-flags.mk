### Compiler-Einstellungen für Make für Module                                ###

MCU := atmega644p
CC := avr-gcc

# Compiler-Einstellungen: Beginn -----------------------------------------------#
CFLAGS := -mmcu=$(MCU) \
	  --all-warnings \
	  --extra-warnings \
	  -Wpedantic \
	  -O \
	  -c
CFLAGS_DEBUG := $(CFLAGS) \
		-gdwarf

# Compiler-Einstellungen: Ende -------------------------------------------------#

# Compiler-Einstellungen für Tests: Beginn -------------------------------------#
TEST_CC := gcc
TEST_CC_FLAGS_EXEC := -Wall \
	              -O \
                      -gdwarf
TEST_CC_FLAGS := $(TEST_CC_FLAGS_EXEC) \
                 -c

# Compiler-Einstellungen für Tests: Ende ---------------------------------------#

