# $Id$

NAME = tcpplus
SECTION = developer/components
THEMEFILENAME = website
DOCTOOLS_BASE = ../../../build

DIA = dia
DOT = dot

XHTMLIMAGES = images/try.png images/virtualB.png images/virtualC.png \
	images/virtualD.png \
	images/class.png images/classB.png images/classD.png \
	images/diamond.png images/classA.png images/classC.png \
	images/graph.png

# Only the automatically-generated images here
CLEAN_EXTRA = images/class.png images/classB.png images/classD.png \
	images/diamond.png images/classA.png images/classC.png images/graph.png

include $(DOCTOOLS_BASE)/docs.mk

images/class.png: images/class.dia
	${DIA} -t png images/class.dia

images/classA.png: images/classA.dia
	${DIA} -t png images/classA.dia

images/classB.png: images/classB.dia
	${DIA} -t png images/classB.dia

images/classC.png: images/classC.dia
	${DIA} -t png images/classC.dia

images/classD.png: images/classD.dia
	${DIA} -t png images/classD.dia

images/diamond.png: images/diamond.dot
	${DOT} -Tpng -o images/diamond.png images/diamond.dot

images/graph.png: images/graph.dot
	${DOT} -Tpng -o images/graph.png images/graph.dot

