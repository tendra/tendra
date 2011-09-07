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


SYNTAX+=	syntax.sid

.include <tendra.sid.mk>


#${obj_c}/tdf.h : ${SRC}/tdf.alg
#	@${REMOVE} ${obj_c}/*.h
#	${CALCULUS} -a -x ${SRC}/tdf.alg ${obj_c}
#
#${obj_tok}/tdf.h : ${SRC}/tdf.alg
#	@${REMOVE} ${obj_tok}/*.h
#	${CALCULUS} -a -x -t ${SRC}/tdf.alg ${obj_tok}
#
#${SRC}/lexer.h : ${SRC}/lexer.lxi
#	@${REMOVE} ${SRC}/lexer.h
#	${LEXI} ${SRC}/lexer.lxi ${SRC}/lexer.h
#
#${SRC}/keyword.h : ${SRC}/lexer.lxi
#	@${REMOVE} ${SRC}/keyword.h
#	${LEXI} -k ${SRC}/lexer.lxi ${SRC}/keyword.h

