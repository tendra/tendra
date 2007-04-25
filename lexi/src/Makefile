# $Id$

# Standard directories and files

#SRCX=${.CURDIR}/../shared

# Standard variables

WARNS?=		3

TCCOPTS=	-Yansi -Xs
CCOPTS=		${TCCOPTS} -I${BASE_DIR}/${INCLUDE} -I${.CURDIR} -I${SRCX}
LIBS=

# Dependencies and construction rules

PROG=		${.CURDIR:T}

SRCS=		char.c error.c lex.c main.c output.c syntax.c xalloc.c

.PATH:	${SRCX}

SIDOPTS=-l ansi-c -s no-lines

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

#.include "../Makefile.inc"

all: lexi

# This is just until I have lexi moved out and cleaned up - kate
lexi: char.o syntax.o lex.o main.o output.o \
	shared/xalloc.c shared/error.c
	$(CC) $(CFLAGS) -o lexi char.o syntax.o lex.o main.o output.o \
		shared/error.c shared/xalloc.c

clean:
	rm -f char.o syntax.o lex.o main.o output.o \
		lexi

