# $Id$

#${SRC6}/syntax1.c : ${SYNTAX}
#   ${SID} ${SIDOPTS} ${SYNTAX} ${SRC6}/syntax@.c ${SRC6}/syntax.h
#
#${SRC5}/psyntax1.c : ${PSYNTAX}
#   ${SID} ${SIDOPTS} ${PSYNTAX} ${SRC5}/psyntax@.c ${SRC5}/psyntax.h


.include "Makefile.inc"


CCOPTS+=	-I ../../common/construct
CCOPTS+=	-I ../../common/obj_c
CCOPTS+=	-I ../../common/output
CCOPTS+=	-I ../../common
CCOPTS+=	-I ../utility

SRCS!=	ls -1 psyntax*.c

SRCS+=	char.c
SRCS+=	charset.c
SRCS+=	constant.c
SRCS+=	file.c
SRCS+=	hash.c
SRCS+=	lex.c
SRCS+=	literal.c
SRCS+=	macro.c
SRCS+=	parse.c
SRCS+=	pragma.c
SRCS+=	predict.c
SRCS+=	preproc.c
SRCS+=	table.c

.include <tendra.obj.mk>

.include <tendra.partial.mk>


SIDOPTS+=	-s unreachable-macro
SIDOPTS+=	-s split=5000

SYNTAX+=	psyntax.sid

.include <tendra.sid.mk>


charset: charset.c
	${CC} -o ${.TARGET} ${CFLAGS} -DCHARSET_TOOL ${.ALLSRC}

