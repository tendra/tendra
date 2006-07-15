# $Id$

# Standard directories and files
SRC1=${.CURDIR}/templ
SPEC=${BASE_DIR}/src/lib/tdf/def_4_1.db

# Standard variables

WARNS?=		2

TCCOPTS=	-Yansi -Xs
CCOPTS=		${TCCOPTS}
LIBS=

# Dependencies and construction rules

PROG=		${.CURDIR:T}

SRCS=		alignment.c analyser.c bitstream.c check.c de_capsule.c\
		de_unit.c decode.c enc_cap.c encode.c eval.c fetch.c file.c\
		help.c high.c main.c node.c read.c read_cap.c shape.c table.c\
		tdf.c utility.c write.c

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

.include "../Makefile.inc"
