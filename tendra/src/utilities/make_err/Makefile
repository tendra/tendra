# $TenDRA$

CFLAGS= -I${.CURDIR} -I${.CURDIR}/../shared -I${.CURDIR}/obj_c -I.
.PATH.c : ${.CURDIR} ${.CURDIR}/.. ${.CURDIR}/../shared ${.CURDIR}/obj_c .
SID_OPTS=	-l ossg-c -s no-lines

PROG = make_err

SRCS=	error.c lex.c main.c process.c syntax.c

#obj_c sources
SRCS+= errors.c

#shared sources
SRCS+= xalloc.c

DEPEND_SRC=	keyword.h lexer.h syntax.c errors.h

errors.h: errors.alg
	${CALCULUS} -a -x ${.CURDIR}/errors.alg ${OBJ_DIR}

keyword.h:
	${LEXI} -k ${.CURDIR}/lexer.lxi ${OBJ_DIR}/${.TARGET}

lexer.h:
	${LEXI} ${.CURDIR}/lexer.lxi ${OBJ_DIR}/${.TARGET}

syntax.c: syntax.sid syntax.act
	${SID} ${SID_OPTS} ${.CURDIR}/syntax.sid ${.CURDIR}/syntax.act \
	${OBJ_DIR}/syntax.c ${OBJ_DIR}/syntax.h

CLEANFILES=	keyword.h lexer.h syntax.c syntax.h

#generated from errors.alg
CLEANFILES+=	assert_def.h entry_ops.h errors.h map_ops.h msg_ops.h \
		name_ops.h param_ops.h

.include "${.CURDIR}/../../../mk/base/tendra.prog.mk"

