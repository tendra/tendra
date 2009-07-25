# $Id$

NAME = orientation
SECTION = developer/guides
THEMEFILENAME = website
DOCTOOLS_BASE =  ../../../../tendra-doc/build

XHTMLIMAGES = images/apibuilding.png images/compilation.png

include $(DOCTOOLS_BASE)/docs.mk

orientation.xml: $(XHTMLIMAGES)

images/apibuilding.png: images/apibuilding.dia
	dia -e $@ images/apibuilding.dia
	mogrify -thumbnail '80%' $@

images/compilation.png: images/compilation.dia
	dia -e $@ images/compilation.dia
	mogrify -thumbnail '80%' $@

