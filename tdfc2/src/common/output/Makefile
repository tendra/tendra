# $Id$

#${SRC4}/tdf1.h : ${SPEC} ${SRC2B}/tdf1.h
#   @${RMFILE} ${SRC4}/tdf1.h
#   ${MAKE_TDF} ${SPEC} ${SRC2B}/tdf1.h ${SRC4}/tdf1.h

.include "Makefile.inc"


CCOPTS+=	-I ../../common/construct
CCOPTS+=	-I ../../common/obj_c
CCOPTS+=	-I ../../common/parse
CCOPTS+=	-I ../../common
CCOPTS+=	-I ../utility

SRCS+=	capsule.c
SRCS+=	compile.c
SRCS+=	decode.c
SRCS+=	diag.c
SRCS+=	diag2.c
SRCS+=	dump.c
SRCS+=	encode.c
SRCS+=	exp.c
SRCS+=	init.c
SRCS+=	load.c
SRCS+=	mangle.c
SRCS+=	save.c
SRCS+=	shape.c
SRCS+=	stmt.c
SRCS+=	struct.c
SRCS+=	throw.c
SRCS+=	tok.c
SRCS+=	unmangle.c

.include <tendra.obj.mk>

.include <tendra.partial.mk>

