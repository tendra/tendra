# $Id$

NAME = lexi.1

PREFIX ?= /usr/local
SHAREDIR ?= ${PREFIX}/share
DOCDIR ?= ${SHAREDIR}/doc
_MANDIR ?= ${PREFIX}/man

DOCTOOLS_BASE ?= ../../build

include $(DOCTOOLS_BASE)/docs.mk

lexi.1.xml: ../cmdsynopsis.xml

install: all
	install -m 755 -d ${_MANDIR}/man1
	install -m 644 ../roff/${NAME} ${_MANDIR}/man1/${NAME}
	install -m 755 -d ${DOCDIR}/lexi/${NAME}-single
	install -m 644 ../xhtml/${NAME}-single/* ${DOCDIR}/lexi/${NAME}-single/
	[ ! -f ../pdf/${NAME}.pdf ] || install -m 755 -d ${DOCDIR}/lexi/${NAME}
	[ ! -f ../pdf/${NAME}.pdf ] || install -m 644 ../pdf/${NAME}.pdf ${DOCDIR}/lexi/${NAME}/

