# $Id$

.include "Makefile.inc"


SRCS+=	hash.c
SRCS+=	index.c
SRCS+=	lex.c
SRCS+=	main.c
SRCS+=	makefile.c
SRCS+=	name.c
SRCS+=	object.c
SRCS+=	print.c
SRCS+=	syntax.c
SRCS+=	type.c
SRCS+=	utility.c
SRCS+=	variable.c

.include <tendra.obj.mk>


PROG=	tspec

.include <tendra.prog.mk>


#SIDOPTS=-s no-lines
#syntax.c syntax.h: syntax.sid syntax.act
#	@${REMOVE} ${SID_OUT}
#	${SID} ${SIDOPTS} syntax.sid syntax.act ${SID_OUT}
#
#${SRC}/lexer.h : ${SRC}/lexer.lxi
#	@${REMOVE} ${SRC}/lexer.h
#	${LEXI} ${SRC}/lexer.lxi ${SRC}/lexer.h
#
#${SRC}/keyword.h : ${SRC}/lexer.lxi
#	@${REMOVE} ${SRC}/keyword.h
#	${LEXI} -k ${SRC}/lexer.lxi ${SRC}/keyword.h
#
#auto_clobber :
#	${REMOVE} ${SID_OUT} ${LEXI_OUT}

