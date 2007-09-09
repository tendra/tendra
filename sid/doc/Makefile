# $Id$

# This is a placeholder for tendra-doc to override.
DOCTOOLS_BASE ?= ../build

all:
	cd guide && ${MAKE} all DOCTOOLS_BASE=../$(DOCTOOLS_BASE)
	cd devguide && ${MAKE} all DOCTOOLS_BASE=../$(DOCTOOLS_BASE)
	cd changelog && ${MAKE} all DOCTOOLS_BASE=../$(DOCTOOLS_BASE)
	cd man && ${MAKE} all pdf DOCTOOLS_BASE=../$(DOCTOOLS_BASE)

clean:
	cd guide && ${MAKE} clean DOCTOOLS_BASE=../$(DOCTOOLS_BASE)
	cd devguide && ${MAKE} clean DOCTOOLS_BASE=../$(DOCTOOLS_BASE)
	cd changelog && ${MAKE} clean DOCTOOLS_BASE=../$(DOCTOOLS_BASE)
	cd man && ${MAKE} clean DOCTOOLS_BASE=../$(DOCTOOLS_BASE)

# TODO This should be moved to doctool's makefile somehow
install:
	cd guide && ${MAKE} install DOCTOOLS_BASE=../$(DOCTOOLS_BASE)
	cd devguide && ${MAKE} install DOCTOOLS_BASE=../$(DOCTOOLS_BASE)
	cd changelog && ${MAKE} install DOCTOOLS_BASE=../$(DOCTOOLS_BASE)
	cd man && ${MAKE} install DOCTOOLS_BASE=../$(DOCTOOLS_BASE)

