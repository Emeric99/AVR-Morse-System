### Makefile für Modul "uart" ###

# Modulname
MODULE := modul-uart

include ../make-module-flags.mk

#-------------------------------------------------------------------------------#

# automatisch abgeleitete Variablen: Beginn ------------------------------------#
MODULE_HARDWARE := $(MODULE)-hardware
OBJECTS := $(MODULE).o \
	   $(MODULE_HARDWARE).o \
           test

MODULE_H := $(MODULE).h
MODULE_HARDWARE_H := $(MODULE_HARDWARE).h
MODULE_HARDWARE_C := $(MODULE_HARDWARE).c
MODULE_C := $(MODULE).c
MODULE_TEST_C := $(MODULE)-test.c
# automatisch abgeleitete Variablen: Ende --------------------------------------#

# Make-Ziele: Beginn -----------------------------------------------------------#
.PHONY: all clean

all: $(OBJECTS)

clean:
	rm -f *.o
	rm -f *.gch
	rm -f test

%.o: %.h %.c
	$(CC) $(CFLAGS_DEBUG) $+
	mv $(*F).o $(*F)-debug.o
	$(CC) $(CFLAGS) $+

test: $(MODULE_TEST_C) $(MODULE_H) $(MODULE_C) -lunittester
	$(TEST_CC) $(TEST_CC_FLAGS_DEBUG) -o $@ $+
# Make-Ziele: Ende -------------------------------------------------------------#


