# $TenDRA$

TCC_OPTS=	-yTENDRA_BASEDIR=${OBJ_PREFIX}/ \
		-Y${DEFAULT_BUILD} \
		-Ydefault.extra \
		-Ypl_tdf \
		-jtarget_tok \
		-J${SRC_DIR}/obj/lib/machines/freebsd/80x86/tokens \
		-J${SRC_DIR}/obj/lib/apis/lib/ansi

LIB=	libtdf.a

SRCS=	version.c INT64.c

INT64.o: INT64a.c INT64b.pl abstract.pl
	${TCC} ${TCC_OPTS} -c -o INT64.o -M -WP,-I${.CURDIR} ${.ALLSRC}


.include "../../../mk/base/tendra.prog.mk"
