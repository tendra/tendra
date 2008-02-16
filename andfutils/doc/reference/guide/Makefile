# $Id$

NAME = guide

DIA = dia

XHTMLIMAGES = images/guide1.png images/guide2.png images/guide3.png \
	images/guidetable1.png images/guidetable2.png images/guidetable3.png

# Only the automatically-generated images here
CLEAN_EXTRA = images/guide1.png images/guide2.png

DOCTOOLS_BASE ?= ../../../build

include $(DOCTOOLS_BASE)/docs.mk

images/guide1.png: images/guide1.dia
	${DIA} -t png images/guide1.dia

images/guide2.png: images/guide2.dia
	${DIA} -t png images/guide2.dia

