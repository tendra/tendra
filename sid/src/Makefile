# $Id$

ESRC=errors
BUILD_ERRORS=${ESRC}/BUILD_ERRORS

TARGETS=gen-errors.o arg-parse.o grammar.o lexer.o \
	main.o output.o parser.o

ERR_OUT=gen-errors.c gen-errors.h

MOVE=mv
REMOVE=rm -f
PERL=perl
SID=sid

# XXX: Do I want to have them removed during clean?
#CLEAN_EXTRA= parser.c junk.h c-parser.c c-junk.h gen-errors.c gen-errors.h

SIDOPTS=-l ansi-c -s numeric -s no-lines

#PARSER_OUT=${SRC}/parser.c ${SRC}/junk.h
#C_OUT=${SRC}/c-parser.c ${SRC}/c-junk.h

EFILES=${ESRC}/arg-parse.e ${ESRC}/c-check.e ${ESRC}/c-code.e \
	${ESRC}/c-lexer.e ${ESRC}/c-parser.e ${ESRC}/error-file.e \
	${ESRC}/for-osif.e ${ESRC}/grammar.e ${ESRC}/lexer.e ${ESRC}/main.e \
	${ESRC}/parser.e ${ESRC}/rule-check.e ${ESRC}/rule-factor.e \
	${ESRC}/rule-firsts.e ${ESRC}/rule-lre.e ${ESRC}/scope.e \
	${ESRC}/table.e ${ESRC}/types.e

all: sid

clean:
	${REMOVE} sid gen-errors.c gen-errors.h ${TARGETS}
	cd rules && ${MAKE} clean
	cd lang-c && ${MAKE} clean
	cd adt && ${MAKE} clean
	cd eds && ${MAKE} clean

sid: ${TARGETS} rules/rules.a lang-c/lang-c.a adt/adt.a eds/eds.a
	${CC} ${CFLAGS} ${LDFLAGS} -o $@ ${TARGETS} \
		rules/rules.a lang-c/lang-c.a adt/adt.a eds/eds.a

rules/rules.a:
	cd rules && ${MAKE} all

adt/adt.a:
	cd adt && ${MAKE} all

eds/eds.a:
	cd eds && ${MAKE} all

lang-c/lang-c.a:
	cd lang-c && ${MAKE} all

parser.c: parser.sid parser.act
	${SID} ${SIDOPTS} parser.sid parser.act tmp.$@ junk.h || ( ${REMOVE} tmp.$@ ; exit 1 )
	${MOVE} tmp.$@ $@

gen-errors.c: ${BUILD_ERRORS} ${EFILES}
	${REMOVE} ${ERR_OUT}; \
	${PERL} ${BUILD_ERRORS} -o gen-errors ${EFILES}

