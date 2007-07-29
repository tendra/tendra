# $Id$

REMOVE=rm -f

all:
	cd guide && ${MAKE} all
	cd man && ${MAKE} all

pdf: _pdf

_pdf:
	cd man && ${MAKE} pdf

clean:
	cd guide && ${MAKE} clean
	cd man && ${MAKE} clean
	${REMOVE} -r xhtml roff pdf

install:
	cd guide && ${MAKE} install
	cd man && ${MAKE} install

