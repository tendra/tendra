# $TenDRA$

CFLAGS+= -I${.CURDIR} -I.
.PATH : ${.CURDIR} ${.CURDIR}/templ .
SID_OPTS=	-l ossg-c -s no-lines

PROG = pl

SRCS=	analyse_sort.c consfile.c decodings.c errors.c \
	find_id.c fnsfile.c includes.c lex.c main.c \
	readstreams.c standardsh.c streams.c syntax.c \
	units.c util.c


DEPEND_SRC=	syntax.c consfile.c consfile.h decodings.c \
		decodings.h encodings.h enc_nos.h fnsfile.c

syntax.c: syntax.sid syntax.act
	${SID} ${SID_OPTS} ${.CURDIR}/syntax.sid ${.CURDIR}/syntax.act \
	${OBJ_DIR}/syntax.c ${OBJ_DIR}/syntax.h

consfile.c: consfile.c-tdf
	${MAKE_TDF} ${.CURDIR}/../../lib/tdf/def_4_1.db ${.IMPSRC} |\
	${SORT} > ${OBJ_DIR}/${.TARGET}

CLEANFILES+=	syntax.c syntax.h consfile.c consfile.h decodings.c decodings.h encodings.h enc_nos.h fnsfile.c

.include "${.CURDIR}/../../../mk/base/tendra.prog.mk"
