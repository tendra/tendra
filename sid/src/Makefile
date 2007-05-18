# $Id$

# Standard directories and files


# Standard variables

# Dependencies and construction rules

TARGETS=gen-errors.o\
		action.o alt.o arg-parse.o basic.o bitvec.o c-check.o\
		c-code.o c-lexer.o c-out-info.o c-out-key.o c-out-nl.o\
		c-out-types.o c-output.o c-parser.o cstring-list.o cstring.o\
		dalloc.o dstring.o entry-list.o entry.o error-file.o error.o\
		exception.o grammar.o istream.o item.o key.o\
		lexer.o main.o name.o non-local.o ostream.o output.o parser.o\
		rstack.o rule-check.o rule-factor.o rule-firsts.o rule-lre.o\
		rule-mutate.o rule-names.o rule-simp.o rule-tail.o rule.o\
		scope.o syntax.o table.o type.o types.o

# XXX: Do I want to have them removed during clean?
#CLEAN_EXTRA= parser.c junk.h c-parser.c c-junk.h gen-errors.c gen-errors.h

#SIDOPTS=-l ansi-c -s numeric -s no-lines

#PARSER_OUT=${SRC}/parser.c ${SRC}/junk.h
#C_OUT=${SRC}/c-parser.c ${SRC}/c-junk.h
ERR_OUT=gen-errors.c gen-errors.h

ESRC=errors
EFILES=${ESRC}/arg-parse.e ${ESRC}/c-check.e ${ESRC}/c-code.e\
	${ESRC}/c-lexer.e ${ESRC}/c-parser.e ${ESRC}/error-file.e\
	${ESRC}/for-osif.e ${ESRC}/grammar.e ${ESRC}/lexer.e ${ESRC}/main.e\
	${ESRC}/parser.e ${ESRC}/rule-check.e ${ESRC}/rule-factor.e\
	${ESRC}/rule-firsts.e ${ESRC}/rule-lre.e ${ESRC}/scope.e\
	${ESRC}/table.e ${ESRC}/types.e

BUILD_ERRORS=${ESRC}/BUILD_ERRORS
PERL=perl

all: sid

clean:
	rm -f sid gen-errors.o gen-errors.c gen-errors.h $(TARGETS)

sid: $(TARGETS) gen-errors.o
	$(CC) $(CFLAGS) -o sid $(TARGETS)

gen-errors.c: ${BUILD_ERRORS} ${EFILES}
	${REMOVE} ${ERR_OUT};\
	${PERL} ${BUILD_ERRORS} -o gen-errors ${EFILES}

