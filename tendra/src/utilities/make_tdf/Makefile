# $Id$

# Standard directories and files

SRCC=${.CURDIR}/obj_c
SRCTOK=${.CURDIR}/obj_tok
SRCX=${.CURDIR}/../shared
SRC=${.CURDIR}

# Standard variables

WARNS?=		2

TCCOPTS=	-Yansi -Xs
CCOPTS=		${TCCOPTS} -I${BASE_DIR}/${INCLUDE} -I${.CURDIR} -I${SRCC}\
		-I${SRCTOK} -I${SRCX} -I${BASE_DIR}/src/shared/error \
		-I${BASE_DIR}/src/shared/xalloc

LDOPTS=		-L${OBJ_DIR}/src/shared/error -L${OBJ_DIR}/src/shared/xalloc
LIBS=		-lerror -lxalloc

# Dependencies and construction rules

PROG=		${.CURDIR:T}

SRCS=		input.c lex.c main.c output.c syntax.c tdf.c

.PATH:		${SRCC} ${SRCTOK} ${SRCX}

CALCULUS=calculus
#LEXI=lexi
#SID=sid
#SIDOPTS=-l ansi-c -s no-lines
#
#SID_OUT=${SRC}/syntax.c ${SRC}/syntax.h
#C_OUT=${SRC2}/tdf.h
#TOK_OUT=${SRC2A}/tdf.h
#LEXI_OUT=${SRC}/lexer.h ${SRC}/keyword.h
#
#auto : ${SID_OUT} ${C_OUT} ${TOK_OUT} ${LEXI_OUT}
#
#${SRC}/syntax.c : ${SRC}/syntax.sid ${SRC}/syntax.act
#	@${REMOVE} ${SID_OUT}
#	${SID} ${SIDOPTS} ${SRC}/syntax.sid ${SRC}/syntax.act ${SID_OUT}

${SRCC}/tdf.h : ${SRC}/tdf.alg
	@${REMOVE} ${SRCC}/*.h
	${CALCULUS} -a -x ${SRC}/tdf.alg ${SRCC}

${SRCTOK}/tdf.h : ${SRC}/tdf.alg
	@${REMOVE} ${SRCTOK}/*.h
	${CALCULUS} -a -x -t ${SRC}/tdf.alg ${SRCTOK}

#${SRC}/lexer.h : ${SRC}/lexer.lxi
#	@${REMOVE} ${SRC}/lexer.h
#	${LEXI} ${SRC}/lexer.lxi ${SRC}/lexer.h
#
#${SRC}/keyword.h : ${SRC}/lexer.lxi
#	@${REMOVE} ${SRC}/keyword.h
#	${LEXI} -k ${SRC}/lexer.lxi ${SRC}/keyword.h

.include "../Makefile.inc"
