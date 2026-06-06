FILES := systemspezifikation
OBJECTS := $(foreach file,$(FILES),$(file).pdf)
INTER_SUFFIXES := aux bbl blg log nav out snm toc toc.old vrb fdb_latexmk fls
INTER_OBJECTS = $(foreach file,$(FILES),$(foreach suffix,$(INTER_SUFFIXES),$(file).$(suffix)))

.PHONY: clean

all: clean spezifikation

spezifikation: systemspezifikation.tex
	rm -f systemspezifikation.pdf
	latexmk -pdf -dvi- -ps- -pdflatex="lualatex" $<
clean:
	rm -f $(INTER_OBJECTS)
	rm -f $(OBJECTS)

