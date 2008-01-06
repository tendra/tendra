# $Id$

.if "${CC}" == "tcc"
CFLAGS=	-Yansi -Xs
.else
CFLAGS+= -Wall
.endif

TEMPL=${.CURDIR}/templ
SPEC=../../lib/make_tdf/def_4_1.db
MAKE_TDF=make_tdf

PROG=		${.CURDIR:T}
OBJS=		alignment.o analyser.o bitstream.o check.o de_capsule.o\
		de_unit.o decode.o enc_cap.o encode.o eval.o fetch.o file.o\
		help.o high.o main.o node.o read.o read_cap.o shape.o table.o\
		tdf.o utility.o write.o


all: ${PROG}

${PROG}: ${OBJS}
	${CC} -o ${PROG} ${OBJS}

clean:
	rm -f ${OBJS} ${PROG}



auto: tdf.c tdf.h check_exp.h

tdf.c: ${SPEC} ${TEMPL}/tdf.c
	rm -f tdf.c
	${MAKE_TDF} ${SPEC} ${TEMPL}/tdf.c tdf.c

tdf.h: ${SPEC} ${TEMPL}/tdf.h
	rm -f tdf.h
	${MAKE_TDF} ${SPEC} ${TEMPL}/tdf.h tdf.h

check_exp.h: ${SPEC} ${TEMPL}/check_exp.h
	rm -f check_exp.h
	${MAKE_TDF} ${SPEC} ${TEMPL}/check_exp.h check_exp.h

auto_clobber:
	rm -f tdf.c tdf.h check_exp.h
