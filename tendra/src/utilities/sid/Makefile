# $TenDRA$

CFLAGS+= -I. -I${.CURDIR} -I${SRC_DIR}/src/include

PROG=	sid

SRCS=	action.c alt.c basic.c bitvec.c c-check.c \
	c-code.c c-lexer.c c-out-info.c c-out-key.c c-out-nl.c c-out-types.c \
	c-output.c c-parser.c cstring-list.c dalloc.c entry-list.c entry.c \
	grammar.c istream.c item.c key.c lexer.c main.c name.c non-local.c \
	output.c parser.c rstack.c rule-check.c rule-factor.c \
	rule-firsts.c rule-lre.c rule-mutate.c rule-names.c rule-simp.c \
	rule-tail.c rule.c scope.c syntax.c table.c type.c types.c

USE_LIBTEN=	yes

CAT_EXTRA=	${.CURDIR}/parser.cat

SID_OPTS= -l iso-c -s no-lines -s numeric-ids

regenerate_cparser:
	${SID} ${SID_OPTS} ${.CURDIR}/c-parser.sid ${.CURDIR}/c-parser.act \
	${.CURDIR}/c-parser.c ${.CURDIR}/c-junk.h

regenerate_parser:
	${SID} ${SID_OPTS} ${.CURDIR}/parser.sid ${.CURDIR}/parser.act \
	${.CURDIR}/parser.c ${.CURDIR}/junk.h

.include "${.CURDIR}/../../../mk/base/tendra.prog.mk"
