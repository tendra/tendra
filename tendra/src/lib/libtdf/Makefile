
# $TenDRA$

TCC_OPTS+=	-yTENDRA_BASEDIR=${OBJ_PREFIX}/ \
		-Y${DEFAULT_BUILD} \
		-Ypl_tdf \
		-jtarget_tok \
		-J${OBJ_PREFIX}/lib/machines/${SRC_MACHINES}/tokens \
		-J${OBJ_PREFIX}/lib/apis/lib/ansi
TCC_OPTS+=	${LIBTDF_CFLAGS}

SHLIB=	libtdf.a

SRCS=	version.c INT64.c

INT64.o: INT64a.c INT64b.pl abstract.pl
	${TCC} ${TCC_OPTS} -c -o INT64.o -M -WP,-I${.CURDIR} ${.ALLSRC}


.include "../../../mk/base/tendra.prog.mk"
