# $Id$

NAME = userguide
XHTMLIMAGES = images/tokens.png

PREFIX ?= /usr/local
SHAREDIR ?= ${PREFIX}/share
DOCDIR ?= ${SHAREDIR}/doc

DOCTOOLS_BASE ?= ../../build

include $(DOCTOOLS_BASE)/docs.mk

userguide.xml: ../cmdsynopsis.xml commands.xml specification.xml

images/tokens.png: images/tokens.dia
	dia -t png images/tokens.dia

install: all
	install -m 755 -d ${DOCDIR}/lexi/${NAME}-single
	install -m 644 ../xhtml/${NAME}-single/* ${DOCDIR}/lexi/${NAME}-single/
	install -m 755 -d ${DOCDIR}/lexi/${NAME}
	install -m 644 ../xhtml/${NAME}/* ${DOCDIR}/lexi/${NAME}/

