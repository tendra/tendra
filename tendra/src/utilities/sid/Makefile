# $TenDRA$

CFLAGS+= -I. -I${.CURDIR} -I${SRC_DIR}/src/include

PROG=	sid

SRCS=	action.c alt.c arg-parse.c basic.c bitvec.c c-check.c c-code.c \
	c-lexer.c c-out-info.c c-out-key.c c-out-nl.c c-out-types.c \
	c-output.c c-parser.c cstring-list.c cstring.c dalloc.c dstring.c \
	entry-list.c entry.c error-file.c error.c exception.c gen-errors.c \
	grammar.c istream.c item.c key.c lexer.c main.c name.c non-local.c \
	ostream.c output.c parser.c rstack.c rule-check.c rule-factor.c \
	rule-firsts.c rule-lre.c rule-mutate.c rule-names.c rule-simp.c \
	rule-tail.c rule.c scope.c syntax.c table.c type.c types.c

DEPEND_SRC=     gen-errors.c

ERRORFILES=	arg-parse.e c-check.e c-code.e c-lexer.e c-parser.e \
		error-file.e for-osif.e grammar.e lexer.e main.e parser.e \
		rule-check.e rule-factor.e rule-firsts.e rule-lre.e scope.e \
		table.e types.e

gen-errors.c:
	${BIN_PERL} -w ${.CURDIR}/errors/BUILD_ERRORS -o ${.OBJDIR}/gen-errors \
	${ERRORFILES:S|^|${.CURDIR}/errors/|}

CLEANFILES+=    gen-errors.c gen-errors.h

regenerate_cparser:
	${SID} ${SID_OPTS} ${.CURDIR}/c-parser.sid ${.CURDIR}/c-parser.act \
	${OBJ_DIR}/c-parser.c ${OBJ_DIR}/c-junk.h

regenerate_parser:
	${SID} ${SID_OPTS} ${.CURDIR}/parser.sid ${.CURDIR}/parser.act \
	${OBJ_DIR}/parser.c ${OBJ_DIR}/junk.h

.include "${.CURDIR}/../../../mk/base/tendra.prog.mk"
