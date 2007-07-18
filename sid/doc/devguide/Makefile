# $Id$

NAME=devguide
SOURCE=devguide.xml
PROJECT_NAME=sid
PROJECT_URL=http://docs.tendra.org/
RESOURCES=../style/docbook.css ../style/common.css
CSSFILE=docbook.css
XHTMLSTYLE=../xsl/tendra-docbook-chunked.xsl
XHTMLSTYLE_SINGLE=../xsl/tendra-docbook-single.xsl

PREFIX?=/usr/local
SHAREDIR?=${PREFIX}/share
DOCDIR?=${SHAREDIR}/doc

INSTALL=install

include ../doctools/Mk/docbook.mk

install: all
	${INSTALL} -m 755 -d ${DOCDIR}/sid/${NAME}-single
	${INSTALL} -m 644 ../xhtml/${NAME}-single/* ${DOCDIR}/sid/${NAME}-single/
	${INSTALL} -m 755 -d ${DOCDIR}/sid/${NAME}
	${INSTALL} -m 644 ../xhtml/${NAME}/* ${DOCDIR}/sid/${NAME}/

