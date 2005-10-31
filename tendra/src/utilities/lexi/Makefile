# $TenDRA$

CFLAGS+= -I${.CURDIR} -I${SRC_DIR}/src/include -I.
.PATH : ${.CURDIR}

USE_LIBTEN=	yes

PROG = lexi

SRCS=	char.c lex.c main.c output.c syntax.c

DEPEND_SRC=	syntax.c

syntax.c: syntax.sid syntax.act
	${SID} ${SID_OPTS} ${.CURDIR}/syntax.sid ${.CURDIR}/syntax.act \
	${OBJ_DIR}/syntax.c ${OBJ_DIR}/syntax.h

CLEANFILES+=	syntax.c syntax.h

keyword.h::
	${LEXI} -k lexer.lxi keyword.h

lexer.h::
	${LEXI} -f lexer.lxi lexer.h

.include "${.CURDIR}/../../../mk/base/tendra.prog.mk"
