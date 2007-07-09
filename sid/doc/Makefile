# $Id$

REMOVE=rm -f

all:
	cd guide && $(MAKE) all
	cd devguide && $(MAKE) all
	cd changelog && $(MAKE) all
	cd man && $(MAKE) all pdf

clean:
	cd guide && $(MAKE) clean
	cd devguide && $(MAKE) clean
	cd changelog && $(MAKE) clean
	cd man && $(MAKE) clean
	${REMOVE} -r roff xhtml

# TODO This should be moved to doctool's makefile somehow
install:
	cd guide && $(MAKE) install
	cd devguide && $(MAKE) install
	cd changelog && $(MAKE) install
	cd man && $(MAKE) install

