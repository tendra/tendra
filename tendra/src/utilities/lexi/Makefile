# $TenDRA$

CFLAGS+= -I${.CURDIR} -I${SRC_DIR}/src/include -I.
.PATH : ${.CURDIR} ${.CURDIR}/../shared

PROG = lexi

SRCS=	catstd.c char.c lex.c main.c output.c syntax.c

LDFLAGS += -L${.OBJDIR}/../../libten
LDADD	+= -lten

DEPEND_SRC=	catstd.c syntax.c

syntax.c: syntax.sid syntax.act
	${SID} ${SID_OPTS} ${.CURDIR}/syntax.sid ${.CURDIR}/syntax.act \
	${OBJ_DIR}/syntax.c ${OBJ_DIR}/syntax.h

CLEANFILES=	syntax.c syntax.h

catstd.c catstd.h: ${.CURDIR}/../../libten/catstd.cat ${.CURDIR}/messages.cat
	${BIN_AWK} -f ${.CURDIR}/../../utilities/mkerr/mkerr.awk -- \
		-c ${.OBJDIR}/catstd.c 	-l ${.OBJDIR}/catstd.h \
		${.ALLSRC}

		
CLEANFILES += catstd.h catstd.c

.include "${.CURDIR}/../../../mk/base/tendra.prog.mk"

