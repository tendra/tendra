# $Id$
#
# The TenDRA Documents Doctools theme. This should not contain specific
# information about locations of source files, other than those which comprise
# the theme itself. This is so that this theme may be included by arbitary
# documents which for some reason might need to use the TenDRA theme, but are
# not part of tendra-doc.
#
# This file contains settings common to all themes.

# TODO default $RESOURCES in doctools to CSSFILE etc

# XHTML
XHTMLSTYLE = $(THEME)/xsl/tendra-docbook-chunked.xsl
XHTMLSTYLE_SINGLE = $(THEME)/xsl/tendra-docbook-single.xsl

# PDF
TEXDIR = $(THEME)/tex
TEXFILE = docbook.tex


# TODO possibly custom params to have on-website documents share css
# with the website itself?


# Inter-document links
DOCTOOLS_DOCSURL ?= http://docs.tendra.org
DOCTOOLS_GLOSSURL ?=
DOCTOOLS_WIKIURL ?= http://trac.tendra.org/wiki/
DOCTOOLS_SOURCEURL ?= http://trac.tendra.org/browser/

