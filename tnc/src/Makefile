# $Id$

.include "Makefile.inc"


PARTS+=	src/shared

.include <tendra.partial.mk>


SRCS+=	alignment.c
SRCS+=	analyser.c
SRCS+=	bitstream.c
SRCS+=	check.c
SRCS+=	de_capsule.c
SRCS+=	de_unit.c
SRCS+=	decode.c
SRCS+=	enc_cap.c
SRCS+=	encode.c
SRCS+=	dot.c
SRCS+=	eval.c
SRCS+=	fetch.c
SRCS+=	file.c
SRCS+=	help.c
SRCS+=	high.c
SRCS+=	main.c
SRCS+=	node.c
SRCS+=	read.c
SRCS+=	read_cap.c
SRCS+=	shape.c
SRCS+=	table.c
SRCS+=	tdf.c
SRCS+=	utility.c
SRCS+=	write.c

.include <tendra.obj.mk>


PROG=	tnc

.include <tendra.prog.mk>


#auto: tdf.c tdf.h check_exp.h
#
#tdf.c: ${SPEC} templ/tdf.c
#	rm -f tdf.c
#	${MAKE_TDF} ${SPEC} templ/tdf.c tdf.c
#
#tdf.h: ${SPEC} templ/tdf.h
#	rm -f tdf.h
#	${MAKE_TDF} ${SPEC} templ/tdf.h tdf.h
#
#check_exp.h: ${SPEC} templ/check_exp.h
#	rm -f check_exp.h
#	${MAKE_TDF} ${SPEC} templ/check_exp.h check_exp.h

