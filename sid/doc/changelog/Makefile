# $Id$

NAME=changelog
SOURCE=changelog.xml
PROJECT_NAME=sid
PROJECT_URL=http://docs.tendra.org/
RESOURCES=../style/docbook.css ../style/common.css
CSSFILE=docbook.css
XHTMLSTYLE=../xsl/tendra-docbook-chunked.xsl
XHTMLSTYLE_SINGLE=../xsl/tendra-docbook-single.xsl

PREFIX?=/usr/local
SHAREDIR?=${PREFIX}/share
DOCDIR?=${SHAREDIR}/doc

all: changelog.xml

include ../doctools/Mk/docbook.mk

install: all
	install -m 755 -d ${DOCDIR}/sid/$(NAME)-single
	install -m 644 ../xhtml/$(NAME)-single/* ${DOCDIR}/sid/$(NAME)-single/


changelog.xml: newsitems-docbook.xml

newsitems-docbook.xml: newsitems.xml
	xsltproc -o newsitems-docbook.xml xsl/news.xsl newsitems.xml

