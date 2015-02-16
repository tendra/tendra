# $Id$

.include "Makefile.inc"

PARTS+=	src/shared
PARTS+=	src/obj_c

.include <tendra.partial.mk>


SRCS+=	input.c
SRCS+=	lex.c
SRCS+=	main.c
SRCS+=	output.c
SRCS+=	syntax.c

.include <tendra.obj.mk>


PROG=	make_tdf

.include <tendra.prog.mk>


SIDOPTS+=	-s unreachable-macro

SYNTAX+=	syntax.sid

.include <tendra.sid.mk>


ALGEBRA_C+=  	tdf.alg
ALGEBRA_TOK+=	tdf.alg

.include <tendra.calculus.mk>


#${SRC}/lexer.h : ${SRC}/lexer.lxi
#	@${RMFILE} ${SRC}/lexer.h
#	${LEXI} ${SRC}/lexer.lxi ${SRC}/lexer.h
#
#${SRC}/keyword.h : ${SRC}/lexer.lxi
#	@${RMFILE} ${SRC}/keyword.h
#	${LEXI} -k ${SRC}/lexer.lxi ${SRC}/keyword.h

