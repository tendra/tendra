# $TenDRA$

CFLAGS=	-I${.CURDIR} -I${.CURDIR}/../shared -I${.CURDIR}/obj_c -I.
.PATH : ${.CURDIR} ${.CURDIR}/../shared ${.CURDIR}/obj_c

PROG=	calculus

SRCS=	calculus.c

#sources in the parent dir
SRCS+=	check.c code.c common.c disk.c lex.c main.c \
	output.c pretty.c print.c read.c syntax.c \
	template.c token.c write.c

#shared sources
SRCS+=	error.c xalloc.c

DEPEND_SRC=	keyword.h lexer.h syntax.c

syntax.c: syntax.sid syntax.act
	${SID} ${SID_OPTS} ${.CURDIR}/syntax.sid ${.CURDIR}/syntax.act \
	${OBJ_DIR}/syntax.c ${OBJ_DIR}/syntax.h

keyword.h:
	${LEXI} -k ${.CURDIR}/lexer.lxi ${OBJ_DIR}/${.TARGET}

lexer.h:
	${LEXI} ${.CURDIR}/lexer.lxi ${OBJ_DIR}/${.TARGET}

CLEANFILES+=	keyword.h lexer.h syntax.c syntax.h

.include "${.CURDIR}/../../../mk/base/tendra.prog.mk"
