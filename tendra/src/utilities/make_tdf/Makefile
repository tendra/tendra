# $TenDRA$

CFLAGS+= -I${.CURDIR}  -I${.CURDIR}/obj_c -I${SRC_DIR}/src/include -I.
.PATH : ${.CURDIR} ${.CURDIR}/obj_c .

PROG = make_tdf

SRCS=	catstd.c input.c lex.c main.c output.c syntax.c

#obj_c sources
SRCS+= tdf.c

DEPEND_SRC=	catstd.c keyword.h lexer.h syntax.c tdf.h

LDFLAGS += -L${.OBJDIR}/../../libten
LDADD	+= -lten

keyword.h:
	${LEXI} -k ${.CURDIR}/lexer.lxi ${OBJ_DIR}/${.TARGET}

lexer.h:
	${LEXI} ${.CURDIR}/lexer.lxi ${OBJ_DIR}/${.TARGET}

tdf.h:
	${CALCULUS} -a -x ${.CURDIR}/tdf.alg ${OBJ_DIR}


syntax.c: syntax.sid syntax.act
	${SID} ${SID_OPTS} ${.CURDIR}/syntax.sid ${.CURDIR}/syntax.act \
	${OBJ_DIR}/syntax.c ${OBJ_DIR}/syntax.h

catstd.c catstd.h: ${.CURDIR}/../../libten/catstd.cat ${.CURDIR}/messages.cat
	${MKERR} -c ${.OBJDIR}/catstd.c -l ${.OBJDIR}/catstd.h ${.ALLSRC}

CLEANFILES= catstd.c catstd.h keyword.h lexer.h syntax.c syntax.h

#tdf generated code
CLEANFILES+=	tdf.h par_ops.h cons_ops.h info_ops.h sort_ops.h \
		link_ops.h spec_ops.h cmd_ops.h assert_def.h

.include "${.CURDIR}/../../../mk/base/tendra.prog.mk"
