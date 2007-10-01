# $Id$

NAME = tcpplus
SECTION = user/guides
THEMEFILENAME = website
DOCTOOLS_BASE = ../../../build

DIA = dia

XHTMLIMAGES = try.png virtualB.png virtualC.png virtualD.png \
	class.png classB.png classD.png diamond.png \
	classA.png classC.png compile.png graph.png

# Only the automatically-generated images here
CLEAN_EXTRA = class.png classB.png classD.png diamond.png \
	classA.png classC.png compile.png graph.png

include $(DOCTOOLS_BASE)/docs.mk

class.png: class.dia
	${DIA} -t png class.dia

classA.png: classA.dia
	${DIA} -t png classA.dia

classB.png: classB.dia
	${DIA} -t png classB.dia

classC.png: classC.dia
	${DIA} -t png classC.dia

classD.png: classD.dia
	${DIA} -t png classD.dia

diamond.png: diamond.dia
	${DIA} -t png diamond.dia

compile.png: compile.dia
	${DIA} -t png compile.dia

graph.png: graph.dia
	${DIA} -t png graph.dia

