# A simple comment-stripping example for Lexi.
# $Id$

INSTALL=install
RMFILE=rm -f
LEXI=lexi

PREFIX?=/usr/local
SHAREDIR?=${PREFIX}/share
EXAMPLEDIR?=${SHAREDIR}/examples

all: stripc

clean:
	${RMFILE} main.o stripc comments.c

install:
	${INSTALL} -m 755 -d ${EXAMPLEDIR}/lexi/stripcomments
	${INSTALL} -m 644 Makefile comments.lxi main.c \
		${EXAMPLEDIR}/lexi/stripcomments


stripc: main.o comments.o
	${CC} ${CFLAGS} ${LIBS} -o stripc main.o comments.o

main.o: main.c comments.o comments.h
	${CC} -c ${CFLAGS} main.c

comments.c: comments.lxi
	${LEXI} comments.lxi comments.c comments.h

