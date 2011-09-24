# $Id$

RMFILE=rm -f
INSTALL=install

PREFIX?=/usr/local
SHAREDIR?=${PREFIX}/share
EXAMPLEDIR?=${SHAREDIR}/examples

SIDOPTS= -s no-terminals -s no-numeric-terminals

all: mcalc

clean:
	${RMFILE} lex.yy.o lex.yy.c rpn.c rpn.h rpn.o infix.c infix.h infix.o mcalc

install:
	${INSTALL} -m 755 -d ${EXAMPLEDIR}/sid/mcalc
	${INSTALL} -m 644 Makefile README calc.act rpn.sid infix.sid lexer.h lex.l \
		${EXAMPLEDIR}/sid/mcalc

mcalc: lex.yy.o infix.o rpn.o
	${CC} -o mcalc lex.yy.o infix.o rpn.o

infix.c infix.h: calc.act infix.sid
	sid $(SIDOPTS) infix.sid calc.act infix.c infix.h

rpn.c rpn.h: calc.act rpn.sid
	sid $(SIDOPTS) rpn.sid calc.act rpn.c rpn.h

lex.yy.c: lex.l infix.h rpn.h
	lex lex.l

