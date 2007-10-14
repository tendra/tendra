# $Id$

INSTALL=install
LEXI=lexi
REMOVE=rm -f
MOVE=mv
SID=sid

CFLAGS+=-Ishared/error -Ishared/xalloc
LDFLAGS+=-Lshared/error -Lshared/xalloc

PREFIX?=/usr/local
BINDIR?=${PREFIX}/bin


all: lexi

# This is just until I have lexi moved out and cleaned up - kate
lexi: depend char.o syntax.o lex.o main.o output.o options.o
	${CC} ${LDFLAGS} -o $@ char.o syntax.o lex.o main.o output.o options.o \
		-lerror -lxalloc

depend:
	cd shared && ${MAKE} -f makefile.standalone

clean:
	${REMOVE} char.o syntax.o lex.o main.o output.o \
		lexer.c keyword.h syntax.h syntax.c lexi
	cd shared && ${MAKE} -f makefile.standalone clean

install: lexi
	${INSTALL} -m 755 -d ${BINDIR}
	${INSTALL} -m 755 lexi ${BINDIR}/

lex.c: lexer.c keyword.h

lexer.c: lexer.lxi
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

