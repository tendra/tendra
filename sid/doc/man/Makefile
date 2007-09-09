# $Id$

NAME = sid.1

DOCTOOLS_BASE ?= ../../build

INSTALL = install

include $(DOCTOOLS_BASE)/docs.mk

PREFIX ?= /usr/local
SHAREDIR ?= ${PREFIX}/share
DOCDIR ?= ${SHAREDIR}/doc
_MANDIR ?= ${PREFIX}/man

install: all
	${INSTALL} -m 755 -d ${_MANDIR}/man1
	${INSTALL} -m 644 ../roff/${NAME} ${_MANDIR}/man1/${NAME}
	${INSTALL} -m 755 -d ${DOCDIR}/sid/${NAME}-single
	${INSTALL} -m 644 ../xhtml/${NAME}-single/* ${DOCDIR}/sid/${NAME}-single/

