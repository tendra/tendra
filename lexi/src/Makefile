# $Id$

INSTALL=install
LEXI=lexi
REMOVE=rm -f
MOVE=mv
SID=sid

PREFIX?=/usr/local
BINDIR?=${PREFIX}/bin


all: lexi

# This is just until I have lexi moved out and cleaned up - kate
lexi: char.o syntax.o lex.o main.o output.o \
	shared/xalloc.a shared/error.a
	${CC} ${CFLAGS} -o $@ char.o syntax.o lex.o main.o output.o \
		shared/error.a shared/xalloc.a

clean:
	${REMOVE} char.o syntax.o lex.o main.o output.o \
		lexer.h keyword.h syntax.h syntax.c \
		lexi
	cd shared && make clean

install: lexi
	${INSTALL} -m 755 -d ${BINDIR}
	${INSTALL} -m 755 lexi ${BINDIR}/

shared/error.a:
	cd shared && make error.a

shared/xalloc.a:
	cd shared && make xalloc.a


lex.c: lexer.h keyword.h

lexer.h: lexer.lxi
	@${REMOVE} $@
	${LEXI} lexer.lxi tmp.$@ \
		|| ( ${REMOVE} tmp.$@ ; exit 1 )
	${MOVE} tmp.$@ $@

keyword.h: lexer.lxi
	@${REMOVE} $@
	${LEXI} -k lexer.lxi tmp.$@ \
		|| ( ${REMOVE} tmp.$@ ; exit 1 )
	${MOVE} tmp.$@ $@


syntax.h: syntax.c

syntax.c: syntax.sid syntax.act
	@${REMOVE} syntax.h syntax.c
	${SID} syntax.sid syntax.act tmp.syntax.c tmp.syntax.h \
		|| ( ${REMOVE} tmp.syntax.{c,h} ; exit 1 )
	${MOVE} tmp.syntax.c syntax.c
	${MOVE} tmp.syntax.h syntax.h

