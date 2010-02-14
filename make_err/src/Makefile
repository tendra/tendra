# $Id$

.include "Makefile.inc"


PARTS+=	src/shared/error
PARTS+=	src/shared/xalloc
PARTS+=	src/obj_c

.include <tendra.partial.mk>


CCOPTS+=	-Ishared

SRCS+=	lex.c
SRCS+=	main.c
SRCS+=	process.c
SRCS+=	syntax.c

.include <tendra.obj.mk>


PROG=	make_err

.include <tendra.prog.mk>


#SIDOPTS=-l ansi-c -s no-lines
#C_OUT=${SRC2}/errors.h
#TOK_OUT=${SRC2A}/errors.h
#LEXI_OUT=${SRC}/lexer.h ${SRC}/keyword.h
#
#auto : ${SID_OUT} ${C_OUT} ${TOK_OUT} ${LEXI_OUT}
#
#syntax.c : syntax.sid syntax.act
#	@${REMOVE} syntax.c syntax.h
#	${SID} ${SIDOPTS} syntax.sid syntax.act syntax.c syntax.h
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

