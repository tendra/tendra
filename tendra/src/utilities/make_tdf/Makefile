# $TenDRA$

CFLAGS+= -I${.CURDIR} -I${.CURDIR}/../shared -I${.CURDIR}/obj_c \
	-I${SRC_DIR}/src/include -I.
.PATH : ${.CURDIR} ${.CURDIR}/../shared ${.CURDIR}/obj_c .
SID_OPTS=	-l ossg-c -s no-lines

PROG = make_tdf

NOMAN=	yes

SRCS=	input.c lex.c main.c output.c syntax.c

#obj_c sources
SRCS+= tdf.c

#shared sources
SRCS+= error.c xalloc.c

DEPEND_SRC=	keyword.h lexer.h syntax.c tdf.h

keyword.h:
	${LEXI} -k ${.CURDIR}/lexer.lxi ${OBJ_DIR}/${.TARGET}

lexer.h:
	${LEXI} ${.CURDIR}/lexer.lxi ${OBJ_DIR}/${.TARGET}

tdf.h:
	${CALCULUS} -a -x ${.CURDIR}/tdf.alg ${OBJ_DIR}


syntax.c: syntax.sid syntax.act
	${SID} ${SID_OPTS} ${.CURDIR}/syntax.sid ${.CURDIR}/syntax.act \
	${OBJ_DIR}/syntax.c ${OBJ_DIR}/syntax.h

CLEANFILES= keyword.h lexer.h syntax.c syntax.h

#tdf generated code
CLEANFILES+=	tdf.h par_ops.h cons_ops.h info_ops.h sort_ops.h \
		link_ops.h spec_ops.h cmd_ops.h assert_def.h

.include "${.CURDIR}/../../../mk/base/tendra.prog.mk"

