# $Id$

RMFILE=rm -f
INSTALL=install
LEXI=lexi

PREFIX?=/usr/local
SHAREDIR?=${PREFIX}/share
EXAMPLEDIR?=${SHAREDIR}/examples

all: brf

clean:
	${RMFILE} braille.c brf main.o

install:
	${INSTALL} -m 755 -d ${EXAMPLEDIR}/lexi/braille
	${INSTALL} -m 644 Makefile braille.lxi main.c test \
		${EXAMPLEDIR}/lexi/braille

brf: main.o
	${CC} ${CFLAGS} ${LIBS} -o brf main.o

main.o: main.c braille.c
	${CC} -c ${CFLAGS} main.c

braille.c: braille.lxi
	${LEXI} braille.lxi braille.c

