# $Id$

# This is a placeholder for tendra-doc to override.
DOCTOOLS_BASE ?= ../../build

all:
	cd reference && $(MAKE) all DOCTOOLS_BASE=../$(DOCTOOLS_BASE)
	cd man && $(MAKE) all DOCTOOLS_BASE=../$(DOCTOOLS_BASE)

clean:
	cd reference && $(MAKE) clean DOCTOOLS_BASE=../$(DOCTOOLS_BASE)
	cd man && $(MAKE) clean DOCTOOLS_BASE=../$(DOCTOOLS_BASE)

