# $Id$

NAME=guide
SOURCE=guide.xml
PROJECT_NAME=lexi
PROJECT_URL=http://docs.tendra.org/
RESOURCES=../style/docbook.css ../style/common.css
CSSFILE=docbook.css
XHTMLSTYLE=../xsl/tendra-docbook-chunked.xsl
XHTMLSTYLE_SINGLE=../xsl/tendra-docbook-single.xsl

CLEAN_EXTRA=tokens.png

include ../doctools/Mk/docbook.mk

tokens.png: tokens.dia
	dia -t png tokens.dia

all: tokens.png
	cp tokens.png $(XHTMLDIR)/$(NAME)
	cp tokens.png $(XHTMLDIR)/$(NAME)-single


