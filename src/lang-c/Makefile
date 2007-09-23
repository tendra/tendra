# $Id$

TARGETS=c-check.o c-code.o c-lexer.o c-out-info.o c-out-key.o \
	c-out-nl.o c-out-types.o c-output.o c-parser.o

MOVE=mv
REMOVE=rm -f
SID=sid
#LEXI=lexi
LEXI=../../../../../lexi/branches/zoned_lexi/src/lexi

# XXX: Do I want to have them removed during clean?
#CLEAN_EXTRA= parser.c junk.h c-parser.c c-junk.h gen-errors.c gen-errors.h

SIDOPTS=-l ansi-c -s numeric -s no-lines

#PARSER_OUT=${SRC}/parser.c ${SRC}/junk.h
#C_OUT=${SRC}/c-parser.c ${SRC}/c-junk.h

all: lang-c.a

clean:
	${REMOVE} lang-c.a ${TARGETS} c-lexi_lexer.c

lang-c.a: ${TARGETS}
	ar r $@ ${TARGETS}
	ranlib $@

c-parser.c: c-parser.sid c-parser.act
	${SID} ${SIDOPTS} c-parser.sid c-parser.act tmp.$@ c-junk.h \
		|| ( ${REMOVE} tmp.$@ ; exit 1 )
	${MOVE} tmp.$@ $@

c-lexer.c: c-lexi_lexer.c

c-lexi_lexer.c: c-lexi_lexer.lxi
	@${REMOVE} c-lexi_lexer.c
	${LEXI} -l C_TOK_ c-lexi_lexer.lxi tmp.$@ \
		|| ( ${REMOVE} tmp.$@ ; exit 1 )
	${MOVE} tmp.$@ $@

