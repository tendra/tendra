# $Id$

# Standard directories and files
SRCX=${.CURDIR}/../shared

# Standard variables

TCCOPTS=	-Yansi -Xs
CCOPTS=		${TCCOPTS} -I${.CURDIR} -I${SRCX}
LIBS=

# Dependencies and construction rules

PROG=		${.CURDIR:T}

SRCS=		char.c error.c lex.c main.c output.c syntax.c xalloc.c

.PATH:	${SRCX}

SIDOPTS=-l ossg-c -s no-lines

#SID_OUT=${SRC}/syntax.c ${SRC}/syntax.h
#LEXI_OUT=${SRC}/lexer.h ${SRC}/keyword.h

#${SRC}/syntax.c : ${SRC}/syntax.sid ${SRC}/syntax.act
#	@${REMOVE} ${SID_OUT}
#	${SID} ${SIDOPTS} ${SRC}/syntax.sid ${SRC}/syntax.act ${SID_OUT}
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

.include "../Makefile.inc"
