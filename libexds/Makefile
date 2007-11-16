# $Id$

PREFIX ?= /usr/local

all:
	for dir in src include; do ( cd $$dir && ${MAKE} all ); done

clean:
	for dir in src include; do ( cd $$dir && ${MAKE} clean ); done

install:
	for dir in src include; do ( cd $$dir && ${MAKE} PREFIX=${PREFIX} install ); done

