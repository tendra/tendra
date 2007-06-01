# $Id$

NAME=sid.1
SOURCE=sid.1.xml
PROJECT_NAME=sid
PROJECT_URL=http://docs.tendra.org/
RESOURCES=../style/docbook.css ../style/common.css
CSSFILE=docbook.css
XHTMLSTYLE=../xsl/tendra-docbook-chunked.xsl
XHTMLSTYLE_SINGLE=../xsl/tendra-docbook-single.xsl

include ../doctools/Mk/man.mk
include ../doctools/Mk/docbook.mk

PREFIX?=/usr/local
SHAREDIR?=${PREFIX}/share
DOCDIR?=${SHAREDIR}/doc
_MANDIR?=${PREFIX}/man

install: all
	install -m 755 -d ${_MANDIR}/man1
	install -m 644 ../roff/$(NAME) ${_MANDIR}/man1/$(NAME)
	install -m 755 -d ${DOCDIR}/sid/$(NAME)-single
	install -m 644 ../xhtml/$(NAME)-single/* ${DOCDIR}/sid/$(NAME)-single/

