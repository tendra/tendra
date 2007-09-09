# $Id$

# This is a placeholder for tendra-doc to override.
DOCTOOLS_BASE ?= ../build

all:
	cd guide && $(MAKE) all DOCTOOLS_BASE=../$(DOCTOOLS_BASE)
	cd man && $(MAKE) all pdf DOCTOOLS_BASE=../$(DOCTOOLS_BASE)

clean:
	cd guide && $(MAKE) clean DOCTOOLS_BASE=../$(DOCTOOLS_BASE)
	cd man && $(MAKE) clean DOCTOOLS_BASE=../$(DOCTOOLS_BASE)

install:
	cd guide && ${MAKE} install DOCTOOLS_BASE=../$(DOCTOOLS_BASE)
	cd man && ${MAKE} install DOCTOOLS_BASE=../$(DOCTOOLS_BASE)

