# $TenDRA$

CFLAGS= -I${.CURDIR} -I${.CURDIR}/.. -I${.CURDIR}/../shared -I.
.PATH.c : ${.CURDIR} ${.CURDIR}/.. ${.CURDIR}/../shared

PROG = lexi

SRCS=	char.c lex.c main.c output.c syntax.c

#shared sources
SRCS+=	error.c xalloc.c

DEPEND_SRC=	syntax.c

syntax.c: syntax.sid syntax.act
	${SID} ${SID_OPTS} ${.CURDIR}/syntax.sid ${.CURDIR}/syntax.act \
	${OBJ_DIR}/syntax.c ${OBJ_DIR}/syntax.h

CLEANFILES=	syntax.c syntax.h

.include "${.CURDIR}/../../../mk/base/tendra.prog.mk"

