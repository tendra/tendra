# $Id$

.if "${CC}" == "tcc"
CFLAGS=	-Yansi -Xs
.else
CFLAGS+= -Wall
.endif


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



# XXX: This should really be made working again.
#
#SRC1=${.CURDIR}/templ
#SPEC=${BASE_DIR}/src/lib/tdf/def_4_1.db
#
#MAKE_TDF=make_tdf
#
#auto : ${SRC}/tdf.c ${SRC}/tdf.h ${SRC}/check_exp.h
#
#${SRC}/tdf.c : ${SPEC} ${SRC1}/tdf.c
#	@${REMOVE} ${SRC}/tdf.c
#	${MAKE_TDF} ${SPEC} ${SRC1}/tdf.c ${SRC}/tdf.c
#
#${SRC}/tdf.h : ${SPEC} ${SRC1}/tdf.h
#	@${REMOVE} ${SRC}/tdf.h
#	${MAKE_TDF} ${SPEC} ${SRC1}/tdf.h ${SRC}/tdf.h
#
#${SRC}/check_exp.h : ${SPEC} ${SRC1}/check_exp.h
#	@${REMOVE} ${SRC}/check_exp.h
#	${MAKE_TDF} ${SPEC} ${SRC1}/check_exp.h ${SRC}/check_exp.h
#
#auto_clobber :
#	${REMOVE} ${SRC}/tdf.c ${SRC}/tdf.h ${SRC}/check_exp.h

