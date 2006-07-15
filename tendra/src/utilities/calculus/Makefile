# $Id$

# Standard directories and files

SRCC=${.CURDIR}/obj_c
SRCTOK=${.CURDIR}/obj_tok
SRCX=${.CURDIR}/../shared

# Standard variables

WARNS?=		2

TCCOPTS=	-Yansi -Xs
CCOPTS=		${TCCOPTS} -I${.CURDIR} -I${SRCC} -I${SRCTOK} -I${SRCX}
LIBS=

# Dependencies and construction rules

PROG=		${.CURDIR:T}

SRCS=		calculus.c check.c code.c common.c disk.c error.c lex.c main.c\
 		output.c pretty.c print.c read.c syntax.c template.c token.c\
		write.c xalloc.c

.PATH:	${SRCC} ${SRCTOK} ${SRCX}

SIDOPTS=-l ansi-c -s no-lines

#SID_OUT=${SRC}/syntax.c ${SRC}/syntax.h
#C_OUT=${SRCC}/calculus.h ${SRCC}/type_ops.h
#TOK_OUT=${SRCTOK}/calculus.h ${SRCTOK}/type_ops.h
#DISK_OUT=${SRC}/read_def.h ${SRC}/write_def.h ${SRC}/print_def.h
#LEXI_OUT=${SRC}/lexer.h ${SRC}/keyword.h

#${SRC}/syntax.c : ${SRC}/syntax.sid ${SRC}/syntax.act
#	@${REMOVE} ${SID_OUT}
#	${SID} ${SIDOPTS} ${SRC}/syntax.sid ${SRC}/syntax.act ${SID_OUT}
#
#${SRCC}/calculus.h : ${SRC}/calculus.alg
#	@${REMOVE} ${SRCC}/*.h
#	${CALCULUS} -a -x ${SRC}/calculus.alg ${SRCC}
#
#${SRCTOK}/calculus.h : ${SRC}/calculus.alg
#	@${REMOVE} ${SRCTOK}/*.h
#	${CALCULUS} -a -x -t ${SRC}/calculus.alg ${SRCTOK}
#
#${SRC}/read_def.h : ${SRC}/calculus.alg ${SRC}/disk.alg
#	@${REMOVE} ${SRC}/read_def.h ${SRC}/write_def.h
#	${CALCULUS} -a -x -d ${SRC}/calculus.alg ${SRC}/disk.alg ${SRC}
#
#${SRC}/print_def.h : ${SRC}/calculus.alg
#	@${REMOVE} ${SRC}/print_def.h
#	${CALCULUS} -a -x -p ${SRC}/calculus.alg ${SRC}
#
#${SRC}/lexer.h : ${SRC}/lexer.lxi
#	@${REMOVE} ${SRC}/lexer.h
#	${LEXI} ${SRC}/lexer.lxi ${SRC}/lexer.h
#
#${SRC}/keyword.h : ${SRC}/lexer.lxi
#	@${REMOVE} ${SRC}/keyword.h
#	${LEXI} -k ${SRC}/lexer.lxi ${SRC}/keyword.h

#auto_clobber :
#	${REMOVE} ${SID_OUT}
#	${REMOVE} ${SRCC}/*.h
#	${REMOVE} ${SRCTOK}/*.h
#	${REMOVE} ${DISK_OUT}
#	${REMOVE} ${LEXI_OUT}

.include "../Makefile.inc"
