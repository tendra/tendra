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


SYNTAX+=	syntax.sid

.include <tendra.sid.mk>


#C_OUT=${SRC2}/errors.h
#TOK_OUT=${SRC2A}/errors.h
#LEXI_OUT=${SRC}/lexer.h ${SRC}/keyword.h
#
#auto : ${C_OUT} ${TOK_OUT} ${LEXI_OUT}
#
#${SRCC}/errors.h : ${SRC}/errors.alg
#	@${REMOVE} ${SRCC}/*.h
#	${CALCULUS} -a -x ${SRC}/errors.alg ${SRCC}
#
#${SRCTOK}/errors.h : ${SRC}/errors.alg
#	@${REMOVE} ${SRCTOK}/*.h
#	${CALCULUS} -a -x -t ${SRC}/errors.alg ${SRCTOK}
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
#	${REMOVE} ${SRC2}/*.h
#	${REMOVE} ${SRC2A}/*.h

