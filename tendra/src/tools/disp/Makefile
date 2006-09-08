# $Id$

# Standard directories and files

SRC1=${SRC}/templ
SPEC=${BASE}/src/lib/tdf/def_4_1.db

# Standard variables

WARNS?=		2

TCCOPTS=	-Yansi -Xs
CCOPTS=		${TCCOPTS} -I${BASE_DIR}/${INCLUDE}

LIBS=

# Dependencies and construction rules

PROG=		${.CURDIR:T}

SRCS=		basic.o binding.o capsule.o file.o main.o pretty.o sort.o tdf.o\
		tree.o unit.o utility.o

#MAKE_TDF=make_tdf
#SED=sed
#
#auto : ${SRC}/tdf.c ${SRC}/tdf.h
#
#${SRC}/tdf.c : ${SPEC} ${SRC1}/tdf.c ${SRC1}/tdf.sed
#	@${REMOVE} ${SRC}/tdf.c
#	${MAKE_TDF} ${SPEC} ${SRC1}/tdf.c | ${SED} -f ${SRC1}/tdf.sed > ${SRC}/tdf.c
#
#${SRC}/tdf.h : ${SPEC} ${SRC1}/tdf.h
#	@${REMOVE} ${SRC}/tdf.h
#	${MAKE_TDF} ${SPEC} ${SRC1}/tdf.h ${SRC}/tdf.h
#
#auto_clobber :
#	${REMOVE} ${SRC}/tdf.c ${SRC}/tdf.h

.include "../Makefile.inc"
