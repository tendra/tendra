# $Id$

.if defined(BOOTSTRAP)
CC=	${OBJ_DIR}/src/tools/tcc/tcc -Y${OBJ_DIR}/src/lib/env/build -yTENDRA_BASEDIR=${OBJ_DIR}/src
.endif

LIB=	cpp
SRCS=	baseinfo.o cmath.o cstring.o cwchar.o exception.o new.o new1.o\
	new2.o new3.o new4.o new5.o new6.o new7.o new8.o pure.o term.o\
	typeinfo.o what.o

.include "../../Makefile.inc"
