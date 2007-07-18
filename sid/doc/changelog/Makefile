# $Id$

NAME=changelog
SOURCE=changelog.xml
PROJECT_NAME=sid
PROJECT_URL=http://docs.tendra.org/
RESOURCES=../style/docbook.css ../style/common.css
CSSFILE=docbook.css
XHTMLSTYLE=../xsl/tendra-docbook-chunked.xsl
XHTMLSTYLE_SINGLE=../xsl/tendra-docbook-single.xsl
CLEAN_EXTRA=newsitems-docbook.xml

PREFIX?=/usr/local
SHAREDIR?=${PREFIX}/share
DOCDIR?=${SHAREDIR}/doc

INSTALL=install
XSLTPROC=xsltproc

all: changelog.xml

include ../doctools/Mk/docbook.mk

install: all
	${INSTALL} -m 755 -d ${DOCDIR}/sid/${NAME}-single
	${INSTALL} -m 644 ../xhtml/${NAME}-single/* ${DOCDIR}/sid/${NAME}-single/

changelog.xml: newsitems-docbook.xml

newsitems-docbook.xml: newsitems.xml
	${XSLTPROC} -o newsitems-docbook.xml xsl/news.xsl newsitems.xml

