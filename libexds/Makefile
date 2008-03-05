# $Id$

PREFIX ?= /usr/local

all:
	for dir in src include/exds examples; do ( cd $$dir && ${MAKE} all ); done

clean:
	for dir in src include/exds tests examples; do ( cd $$dir && ${MAKE} clean ); done

install:
	for dir in src include/exds; do ( cd $$dir && ${MAKE} PREFIX=${PREFIX} install ); done

test: all
	cd tests && ${MAKE} test

