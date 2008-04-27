# $Id$

NAME = orientation
SECTION = developer/guides
THEMEFILENAME = website
DOCTOOLS_BASE =  ../../../../tendra-doc/build

XHTMLIMAGES = apibuilding.png compilation.png

include $(DOCTOOLS_BASE)/docs.mk

orientation.xml: $(XHTMLIMAGES)

apibuilding.png: apibuilding.dia
	dia -e $@ apibuilding.dia
	mogrify -thumbnail '80%' $@

compilation.png: compilation.dia
	dia -e $@ compilation.dia
	mogrify -thumbnail '80%' $@

