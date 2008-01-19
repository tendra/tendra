# $Id$

TARGETS=c-check.o c-code.o c-lexer.o c-out-info.o c-out-key.o \
	c-out-nl.o c-out-types.o c-output.o c-parser.o c-lexi_lexer.o \
	persistent.o

MOVE=mv
REMOVE=rm -f
SID=sid
LEXI=lexi

# XXX: Do I want to have them removed during clean?
#CLEAN_EXTRA= parser.c junk.h c-parser.c c-junk.h gen-errors.c gen-errors.h

SIDOPTS=-l ansi-c -s numeric -s no-lines

#PARSER_OUT=${SRC}/parser.c ${SRC}/junk.h
#C_OUT=${SRC}/c-parser.c ${SRC}/c-junk.h

all: lang-c.a

clean:
	${REMOVE} lang-c.a ${TARGETS}

maintainer-clean:
	${REMOVE} c-lexi_lexer.c

lang-c.a: ${TARGETS}
	ar r $@ ${TARGETS}
	ranlib $@

c-parser.c: c-parser.sid c-parser.act
	${SID} ${SIDOPTS} c-parser.sid c-parser.act tmp.$@ c-junk.h \
		|| ( ${REMOVE} tmp.$@ ; exit 1 )
	${MOVE} tmp.$@ $@

c-lexer.c: c-lexi_lexer.c

c-lexi_lexer.h c-lexi_lexer.c: c-lexi_lexer.lxi c-lexi_lexer.lct
	-${MOVE} c-lexi_lexer.c sav.c-lexi_lexer.c 
	-${MOVE} c-lexi_lexer.h sav.c-lexi_lexer.h
	${LEXI} -t C_TOK_ -p c_lexi_ -lC99 -a c-lexi_lexer.lxi c-lexi_lexer.lct c-lexi_lexer.c c-lexi_lexer.h \
		|| ( ${MOVE} sav.c-lexi_lexer.c c-lexi_lexer.c ; ${MOVE} sav.c-lexi_lexer.h c-lexi_lexer.h ; exit 1 )


