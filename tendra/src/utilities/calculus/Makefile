# $TenDRA$

CFLAGS+= -I${.CURDIR} -I${.CURDIR}/obj_c \
	-I${SRC_DIR}/src/include -I.
.PATH : ${.CURDIR} ${.CURDIR}/obj_c

PROG=	calculus

SRCS=	calculus.c

#sources in the parent dir
SRCS+=	catstd.c check.c code.c common.c disk.c lex.c main.c \
	output.c pretty.c print.c read.c syntax.c \
	template.c token.c write.c

LDFLAGS += -L${.OBJDIR}/../../libten
LDADD	+= -lten

DEPEND_SRC=	catstd.c keyword.h lexer.h syntax.c

syntax.c: syntax.sid syntax.act
	${SID} ${SID_OPTS} ${.CURDIR}/syntax.sid ${.CURDIR}/syntax.act \
	${OBJ_DIR}/syntax.c ${OBJ_DIR}/syntax.h

keyword.h:
	${LEXI} -k ${.CURDIR}/lexer.lxi ${OBJ_DIR}/${.TARGET}

lexer.h:
	${LEXI} ${.CURDIR}/lexer.lxi ${OBJ_DIR}/${.TARGET}

catstd.c catstd.h: ${.CURDIR}/../../libten/catstd.cat ${.CURDIR}/messages.cat
	${BIN_AWK} -f ${.CURDIR}/../../utilities/mkerr/mkerr.awk -- \
		-c ${.OBJDIR}/catstd.c 	-l ${.OBJDIR}/catstd.h \
		${.ALLSRC}

CLEANFILES+=	catstd.h catstd.c keyword.h lexer.h syntax.c syntax.h

.include "${.CURDIR}/../../../mk/base/tendra.prog.mk"
