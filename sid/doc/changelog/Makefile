# $Id$

NAME = changelog

PREFIX ?= /usr/local
SHAREDIR ?= ${PREFIX}/share
DOCDIR ?= ${SHAREDIR}/doc

DOCTOOLS_BASE ?= ../../build

INSTALL=install
XSLTPROC=xsltproc

all: changelog.xml

include $(DOCTOOLS_BASE)/docs.mk

install: all
	${INSTALL} -m 755 -d ${DOCDIR}/sid/${NAME}-single
	${INSTALL} -m 644 ../xhtml/${NAME}-single/* ${DOCDIR}/sid/${NAME}-single/

changelog.xml: newsitems-docbook.xml

newsitems-docbook.xml: newsitems.xml
	${XSLTPROC} -o newsitems-docbook.xml xsl/news.xsl newsitems.xml

