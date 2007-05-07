# $Id$

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
	shared/xalloc.a shared/error.a
	$(CC) $(CFLAGS) -o lexi char.o syntax.o lex.o main.o output.o \
		shared/error.a shared/xalloc.a

clean:
	rm -f char.o syntax.o lex.o main.o output.o \
		lexi
	cd shared && make clean

install:

shared/error.a:
	cd shared && make error.a

shared/xalloc.a:
	cd shared && make xalloc.a

