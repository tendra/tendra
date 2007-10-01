# $Id$

NAME = porting
SECTION = papers
THEMEFILENAME = website
DOCTOOLS_BASE = ../../build

DIA = dia

XHTMLIMAGES = eg_scheme.png tdf_scheme.png token_args.png \
	tdf_link.png token.png trad_scheme.png

# Only the automatically-generated images here
CLEAN_EXTRA = eg_scheme.png

include $(DOCTOOLS_BASE)/docs.mk

eg_scheme.png: eg_scheme.dia
	${DIA} -t png eg_scheme.dia

