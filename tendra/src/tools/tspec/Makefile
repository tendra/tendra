# $TenDRA$

CFLAGS+= -I${.CURDIR} -I${SRC_DIR}/src/include -I.
.PATH : ${.CURDIR}

PROG = tspec

SRCS=	hash.c index.c lex.c main.c makefile.c name.c \
	object.c print.c syntax.c type.c utility.c \
	variable.c

USE_LIBTEN=	yes

DEPEND_SRC=	syntax.c keyword.h lexer.h

syntax.c: syntax.sid syntax.act
	${SID} ${SID_OPTS} ${.CURDIR}/syntax.sid ${.CURDIR}/syntax.act \
	${OBJ_DIR}/syntax.c ${OBJ_DIR}/syntax.h

keyword.h:
	${LEXI} -k ${.CURDIR}/lexer.lxi ${OBJ_DIR}/${.TARGET}

lexer.h:
	${LEXI} ${.CURDIR}/lexer.lxi ${OBJ_DIR}/${.TARGET}

CLEANFILES+=	syntax.h syntax.c keyword.h lexer.h

.include "${.CURDIR}/../../../mk/base/tendra.prog.mk"
