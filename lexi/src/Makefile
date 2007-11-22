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
		lexer.c lexer.h syntax.h syntax.c lexi
	cd shared && ${MAKE} -f makefile.standalone clean

install: lexi
	${INSTALL} -m 755 -d ${BINDIR}
	${INSTALL} -m 755 lexi ${BINDIR}/

lex.o: lexer.c lexer.h
syntax.o: lexer.h

main.o char.o syntax.o output.o: char.h
lex.o main.o syntax.o : syntax.h
main.o output.o : output.h
main.o options.o output.o : options.h

lexer.c lexer.h: lexer.lxi COPYING
	-${MOVE} lexer.c sav.lexer.c 
	-${MOVE} lexer.h sav.lexer.h
	${LEXI} lexer.lxi lexer.c lexer.h \
		|| ( ${MOVE} sav.lexer.c lexer.c ; ${MOVE} sav.lexer.h lexer.h ; exit 1 )


syntax.h: syntax.c

syntax.c: syntax.sid syntax.act
	@${REMOVE} syntax.h syntax.c
	${SID} syntax.sid syntax.act tmp.syntax.c tmp.syntax.h \
		|| ( ${REMOVE} tmp.syntax.{c,h} ; exit 1 )
	${MOVE} tmp.syntax.c syntax.c
	${MOVE} tmp.syntax.h syntax.h

