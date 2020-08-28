# $Id$

#${SRC4}/tdf1.h : ${SPEC} ${SRC2B}/tdf1.h
#   @${RMFILE} ${SRC4}/tdf1.h
#   ${MAKE_TDF} ${SPEC} ${SRC2B}/tdf1.h ${SRC4}/tdf1.h

.include "Makefile.inc"


CCOPTS+=	-I ../../common/construct
CCOPTS+=	-I ../../common/obj_c
CCOPTS+=	-I ../../common/parse
CCOPTS+=	-I ../../common

TCCOPTS.load.c+=	-Yposix

SRCS+=	load.c
SRCS+=	save.c

.include <tendra.obj.mk>

.include <tendra.partial.mk>

