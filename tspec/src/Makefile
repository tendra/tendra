# $Id$

.include "Makefile.inc"


PARTS+=	src/shared
PARTS+=	src/out

.include <tendra.partial.mk>


TCCOPTS+= -Yposix

SRCS+=	hash.c
SRCS+=	lex.c
SRCS+=	main.c
SRCS+=	name.c
SRCS+=	object.c
SRCS+=	syntax.c
SRCS+=	type.c
SRCS+=	utility.c
SRCS+=	variable.c

.include <tendra.obj.mk>


PROG=	tspec

.include <tendra.prog.mk>


SYNTAX+=	syntax.sid

.include <tendra.sid.mk>


#${SRC}/lexer.h : ${SRC}/lexer.lxi
#	@${RMFILE} ${SRC}/lexer.h
#	${LEXI} ${SRC}/lexer.lxi ${SRC}/lexer.h
#
#${SRC}/keyword.h : ${SRC}/lexer.lxi
#	@${RMFILE} ${SRC}/keyword.h
#	${LEXI} -k ${SRC}/lexer.lxi ${SRC}/keyword.h

