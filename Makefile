### Makefile für das Hauptprogramm                                            ###

include make-main-flags.mk

#-------------------------------------------------------------------------------#
MCU_PROG := m644p
# Taktfrequenz
F_CPU := 16000000

# Module: Beginn ---------------------------------------------------------------#

# Liste der einzukompilierenden Module
MODULES := modul-decoder modul-display modul-ringbuffer modul-signal-extractor modul-encoder modul-morse-generator modul-uart
# 
SUFFIXES := .o -hardware.o
SUFFIXES_DEBUG := -debug.o -hardware-debug.o
MODULE_OBJECTS := $(foreach module,$(MODULES),\
		  $(foreach suffix,$(SUFFIXES),\
		  $(module)/$(module)$(suffix)))
MODULE_OBJECTS_DEBUG := $(foreach module,$(MODULES),\
			$(foreach suffix,$(SUFFIXES_DEBUG),\
			$(module)/$(module)$(suffix)))
# Module: Ende -----------------------------------------------------------------#
#
# Programmeinstellungen, Programmname, Programmteile: Beginn -------------------#

OBJECT := main
INCLUDES := init.c run.c $(MODULE_OBJECTS)
INCLUDES_DEBUG := init.c run.c $(MODULE_OBJECTS_DEBUG)

# Programmeinstellungen, Programmname, Programmteile: Ende ---------------------#
#
# Simulator-Einstellungen: Beginn ----------------------------------------------#

SIMULATOR := simavr

# Simulator-Einstellungen: Ende ------------------------------------------------#

# Make-Ziel: Beginn ------------------------------------------------------------#
.PHONY: all $(MODULES)

all: $(MODULES) $(OBJECT).hex

clean:
	rm -f *.elf
	rm -f *.hex
	rm -f *.vcd
	for module in $(MODULES); do $(MAKE) -C $$module clean; done

$(MODULES):
	$(MAKE) -C $@

%.hex: %.elf
	avr-objcopy -O ihex $< $@

%-firm: %.hex
	avrdude -p $(MCU_PROG) -c linuxgpio -v -U $<

%-debug.elf: %.c $(MODULES)
	$(CC) $(CFLAGS_DEBUG) -o $@ $< $(INCLUDES_DEBUG)

%.elf: %.c $(MODULES)
	$(CC) $(CFLAGS) -o $@ $< $(INCLUDES)

# Die Option
#  -Wl,--undefined=_mmcu,--section-start=.mmcu=0x910000
# ist seltsam, aber bewahrt den Wert .mmcu in der Hex-Datei und lässt
# diesen nicht wegoptimieren. Das ist für den Testbetrieb in der Simulation wichtig.
%-sim.elf: %-sim.c $(MODULES)
	$(CC) $(CFLAGS) \
	-Wl,--undefined=_mmcu,--section-start=.mmcu=0x910000 \
	-o $@ $< $(INCLUDES)

%-sim-debug.elf: %-sim.c $(MODULES)
	$(CC) $(CFLAGS_DEBUG) \
	-Wl,--undefined=_mmcu,--section-start=.mmcu=0x910000 \
	-o $@ $< $(INCLUDES_DEBUG)

%-simulation: %-sim.elf
	$(SIMULATOR) -m $(MCU) -f $(F_CPU) $< -i "hallo_welt.sec"

%-simulation-debug: %-sim-debug.elf
	$(SIMULATOR) -g -m $(MCU) -f $(F_CPU) $<

# Make-Ziele: Ende -------------------------------------------------------------#

