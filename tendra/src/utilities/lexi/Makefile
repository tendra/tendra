# $TenDRA$

CFLAGS+= -I${.CURDIR} -I${.CURDIR}/../shared -I${SRC_DIR}/src/include -I.
.PATH : ${.CURDIR} ${.CURDIR}/../shared

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

