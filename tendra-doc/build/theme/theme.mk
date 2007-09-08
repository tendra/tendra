# $Id$
#
# The TenDRA Documents Doctools theme. This should not contain specific
# information about locations of source files, other than those which comprise
# the theme itself. This is so that this theme may be included by arbitary
# documents which for some reason might need to use the TenDRA theme, but are
# not part of tendra-doc.

# TODO default $RESOURCES to CSSFILE etc

# XHTML
RESOURCES = $(THEME)/css/docs $(THEME)/css/common
CSSFILE = docs/docs.css
XHTMLSTYLE = $(THEME)/xsl/tendra-docbook-chunked.xsl
XHTMLSTYLE_SINGLE = $(THEME)/xsl/tendra-docbook-single.xsl

# PDF
# Assuming $THEMEDIR is $DOCTOOLS_BASE (see ../docs.mk)
TEXDIR = $(DOCTOOLSBASE_FROM_PDFDIR)/$(THEMENAME)/tex
TEXFILE = docbook.tex


# TODO possibly custom params to have on-website documents share css
# with the website itself?

