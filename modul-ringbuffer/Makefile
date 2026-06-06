### Makefile für Modul                                                        ###

# Modulname
# TODO Benenne AAA in richtigen Modulnamen um
MODULE := modul-ringbuffer
# TODO Trage hier Modulabhängigkeiten ein
# Beispiel:
# TEST_INCLUDES := ../modul-BBB/modul-BBB_test.o
TEST_INCLUDES := 

#-------------------------------------------------------------------------------#

include ../make-module-flags.mk

#-------------------------------------------------------------------------------#

# automatisch abgeleitete Variablen: Beginn ------------------------------------#
MODULE_HARDWARE := $(MODULE)-hardware
OBJECTS := $(MODULE)_test.o \
           $(MODULE).o \
           $(MODULE_HARDWARE).o \
           test

MODULE_H := $(MODULE).h
MODULE_C := $(MODULE).c
MODULE_HARDWARE_H := $(MODULE_HARDWARE).h
MODULE_HARDWARE_C := $(MODULE_HARDWARE).c
MODULE_TEST_C := $(MODULE)-test.c
# automatisch abgeleitete Variablen: Ende --------------------------------------#

# Make-Ziele: Beginn -----------------------------------------------------------#
.PHONY: all clean

all: $(OBJECTS)

clean:
	rm -f *.o
	rm -f *.gch
	rm -f test

%_test.o: %.h %.c
	$(TEST_CC) $(TEST_CC_FLAGS) $+
	mv $(*F).o $@

%.o: %.h %.c
	$(CC) $(CFLAGS_DEBUG) $+
	cp $(*F).o $(*F)-debug.o
	avr-strip --strip-debug $@

test: $(MODULE_TEST_C) $(MODULE_H) $(MODULE)_test.o $(TEST_INCLUDES) -lunittester
	$(TEST_CC) $(TEST_CC_FLAGS_EXEC) -o $@ $+
	./test --only-errors
# Make-Ziele: Ende -------------------------------------------------------------#

