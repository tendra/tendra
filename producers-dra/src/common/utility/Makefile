# $Id$

#${SRC7}/errors1.h : ${SRC7}/catalog.err
#   @${REMOVE} ${SRC7}/errors1.h
#   ${MAKE_ERR} ${SRC7}/catalog.err ${SRC7}/errors1.h
#
#${SRC7}/errors2.h : ${SRC7}/catalog.err ${SRC7}/extra.err
#   @${REMOVE} ${SRC7}/errors2.h
#   ${CAT} ${SRC7}/catalog.err ${SRC7}/extra.err | ${MAKE_ERR} > ${SRC7}/errors2.h
#
#${SRC7}/errors3.h : ${SRC7}/catalog.err ${SRC7}/extra.err
#   @${REMOVE} ${SRC7}/errors3.h
#   ${CAT} ${SRC7}/catalog.err ${SRC7}/extra.err | ${MAKE_ERR} -d > ${SRC7}/errors3.h
#
#${SRC7}/opts.h : ${SRC7}/catalog.err
#   @${REMOVE} ${SRC7}/opts.h
#   ${MAKE_ERR} -u ${SRC7}/catalog.err ${SRC7}/opts.h

.include "Makefile.inc"

CCOPTS+=	-I ../../common/construct
CCOPTS+=	-I ../../common/obj_c
CCOPTS+=	-I ../../common/output
CCOPTS+=	-I ../../common/parse
CCOPTS+=	-I ../../common

SRCS+=	buffer.c
SRCS+=	catalog.c
SRCS+=	debug.c
SRCS+=	error.c
SRCS+=	option.c
SRCS+=	print.c
SRCS+=	system.c
SRCS+=	xalloc.c

.include <tendra.obj.mk>

.include <tendra.partial.mk>

