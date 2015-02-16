# $Id$

.include "Makefile.inc"


PARTS+=	src/shared
PARTS+=	src/obj_c

.include <tendra.partial.mk>


SRCS+=	lex.c
SRCS+=	main.c
SRCS+=	process.c
SRCS+=	syntax.c

.include <tendra.obj.mk>


PROG=	make_err

.include <tendra.prog.mk>


SIDOPTS+=	-s unreachable-macro

SYNTAX+=	syntax.sid

.include <tendra.sid.mk>


ALGEBRA_C+=  	errors.alg
ALGEBRA_TOK+=	errors.alg

.include <tendra.calculus.mk>


#C_OUT=${SRC2}/errors.h
#TOK_OUT=${SRC2A}/errors.h
#LEXI_OUT=${SRC}/lexer.h ${SRC}/keyword.h
#
#auto : ${LEXI_OUT}
#
#${SRC}/lexer.h : ${SRC}/lexer.lxi
#	@${RMFILE} ${SRC}/lexer.h
#	${LEXI} ${SRC}/lexer.lxi ${SRC}/lexer.h
#
#${SRC}/keyword.h : ${SRC}/lexer.lxi
#	@${RMFILE} ${SRC}/keyword.h
#	${LEXI} -k ${SRC}/lexer.lxi ${SRC}/keyword.h
#
#auto_clobber :
#	${RMFILE} ${SID_OUT} ${LEXI_OUT}

