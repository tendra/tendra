# $Id$

.if defined(BOOTSTRAP)
CC=     ${OBJ_DIR}/src/tools/tcc/tcc -Y${OBJ_DIR}/src/lib/env/build -yTENDRA_BASEDIR=${OBJ_DIR}/src
.endif

LIB=	tdf
SRCS=	INT64a.o version.o
TPLOPTS=	-I${.CURDIR}

INT64a.o: INT64a.j INT64b.j abstract.j
	${CC} -c -o ${.TARGET} INT64a.j INT64b.j abstract.j -jtarget_tok -M

.include "../Makefile.inc"
