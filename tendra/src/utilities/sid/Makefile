# $Id$

# Standard directories and files
SRC2=	${.CURDIR}/errors

# Standard variables

TCCOPTS=	-Yansi -Xs
CCOPTS=		${TCCOPTS}
LIBS=

# Dependencies and construction rules

PROG=		${.CURDIR:T}
CCOPTS=		${TCCOPTS} -I${.CURDIR}
SRCS=		action.c alt.c arg-parse.c basic.c bitvec.c c-check.c\
		c-code.c c-lexer.c c-out-info.c c-out-key.c c-out-nl.c\
		c-out-types.c c-output.c c-parser.c cstring-list.c cstring.c\
		dalloc.c dstring.c entry-list.c entry.c error-file.c error.c\
		exception.c gen-errors.c grammar.c istream.c item.c key.c\
		lexer.c main.c name.c non-local.c ostream.c output.c parser.c\
		rstack.c rule-check.c rule-factor.c rule-firsts.c rule-lre.c\
		rule-mutate.c rule-names.c rule-simp.c rule-tail.c rule.c\
		scope.c syntax.c table.c type.c types.c

# XXX: Do I want to have them removed during clean?
#CLEAN_EXTRA= parser.c junk.h c-parser.c c-junk.h gen-errors.c gen-errors.h

SIDOPTS=-l ansi-c -s numeric -s no-lines

#PARSER_OUT=${SRC}/parser.c ${SRC}/junk.h
#C_OUT=${SRC}/c-parser.c ${SRC}/c-junk.h
ERR_OUT=gen-errors.c gen-errors.h

EFILES=${SRC2}/arg-parse.e ${SRC2}/c-check.e ${SRC2}/c-code.e\
 ${SRC2}/c-lexer.e ${SRC2}/c-parser.e ${SRC2}/error-file.e\
 ${SRC2}/for-osif.e ${SRC2}/grammar.e ${SRC2}/lexer.e ${SRC2}/main.e\
 ${SRC2}/parser.e ${SRC2}/rule-check.e ${SRC2}/rule-factor.e\
 ${SRC2}/rule-firsts.e ${SRC2}/rule-lre.e ${SRC2}/scope.e\
 ${SRC2}/table.e ${SRC2}/types.e

gen-errors.c: ${SRC2}/BUILD_ERRORS ${EFILES}
	${REMOVE} ${ERR_OUT};\
	${SRC2}/BUILD_ERRORS -o gen-errors ${EFILES}

auto_clobber :
	${REMOVE} ${PARSER_OUT} ${C_OUT} ${ERR_OUT}

.include "../Makefile.inc"
