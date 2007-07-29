# $Id$

NAME=lexi.1
SOURCE=lexi.1.xml
PROJECT_NAME=lexi
PROJECT_URL=http://docs.tendra.org/
RESOURCES=../style/docbook.css ../style/common.css
CSSFILE=docbook.css
XHTMLSTYLE=../xsl/tendra-docbook-chunked.xsl
XHTMLSTYLE_SINGLE=../xsl/tendra-docbook-single.xsl

TEXFILE=docbook.tex
TEXINPUTS=../style/tex

PREFIX?=/usr/local
SHAREDIR?=${PREFIX}/share
DOCDIR?=${SHAREDIR}/doc
_MANDIR?=${PREFIX}/man

lexi.1.xml: ../cmdsynopsis.xml

include ../doctools/Mk/man.mk
include ../doctools/Mk/docbook.mk

install: all
	install -m 755 -d ${_MANDIR}/man1
	install -m 644 ../roff/${NAME} ${_MANDIR}/man1/${NAME}
	install -m 755 -d ${DOCDIR}/lexi/${NAME}-single
	install -m 644 ../xhtml/${NAME}-single/* ${DOCDIR}/lexi/${NAME}-single/
	[ ! -f ../pdf/${NAME}.pdf ] || install -m 755 -d ${DOCDIR}/lexi/${NAME}
	[ ! -f ../pdf/${NAME}.pdf ] || install -m 644 ../pdf/${NAME}.pdf ${DOCDIR}/lexi/${NAME}/

