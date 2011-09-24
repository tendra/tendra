# $Id$

RMFILE=rm -f
INSTALL=install

PREFIX?=/usr/local
SHAREDIR?=${PREFIX}/share
EXAMPLEDIR?=${SHAREDIR}/examples

all: calc

clean:
	${RMFILE} lex.yy.o lex.yy.c calc.o calc.c calc.h calc

install:
	${INSTALL} -m 755 -d ${EXAMPLEDIR}/sid/calc
	${INSTALL} -m 644 Makefile README calc.act calc.sid lex.l \
		${EXAMPLEDIR}/sid/calc

calc: lex.yy.o calc.o
	${CC} -o calc lex.yy.o calc.o

calc.c: calc.act calc.sid
	sid calc.sid calc.act calc.c calc.h

lex.yy.c: lex.l calc.c
	lex lex.l

