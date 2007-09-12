# $Id$

# Standard directories and files

SRCC=${.CURDIR}/obj_c
SRCTOK=${.CURDIR}/obj_tok
SRCX=${.CURDIR}/../shared
SRC=${.CURDIR}

# Standard variables

WARNS?=		2

TCCOPTS=	-Yposix2 -Xs
CCOPTS=		${TCCOPTS} -I${BASE_DIR}/${INCLUDE} -I${.CURDIR} -I${SRCC}\
		-I${SRCTOK} -I${SRCX} -I${BASE_DIR}/src/shared/error \
		-I${BASE_DIR}/src/shared/xalloc

LDOPTS=		-L${OBJ_DIR}/src/shared/error -L${OBJ_DIR}/src/shared/xalloc
LIBS=		-lerror -lxalloc

# Dependencies and construction rules

PROG=		${.CURDIR:T}

SRCS=		lex.c main.c process.c syntax.c errors.c

.PATH:		${SRCC} ${SRCTOK} ${SRCX}

CALCULUS=calculus
#LEXI=lexi
#SID=sid
#SIDOPTS=-l ansi-c -s no-lines
#
#SID_OUT=${SRC}/syntax.c ${SRC}/syntax.h
#C_OUT=${SRC2}/errors.h
#TOK_OUT=${SRC2A}/errors.h
#LEXI_OUT=${SRC}/lexer.h ${SRC}/keyword.h
#
#auto : ${SID_OUT} ${C_OUT} ${TOK_OUT} ${LEXI_OUT}
#
#${SRC}/syntax.c : ${SRC}/syntax.sid ${SRC}/syntax.act
#	@${REMOVE} ${SID_OUT}
#	${SID} ${SIDOPTS} ${SRC}/syntax.sid ${SRC}/syntax.act ${SID_OUT}

${SRCC}/errors.h : ${SRC}/errors.alg
	@${REMOVE} ${SRCC}/*.h
	${CALCULUS} -a -x ${SRC}/errors.alg ${SRCC}

${SRCTOK}/errors.h : ${SRC}/errors.alg
	@${REMOVE} ${SRCTOK}/*.h
	${CALCULUS} -a -x -t ${SRC}/errors.alg ${SRCTOK}

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

.include "../Makefile.inc"
