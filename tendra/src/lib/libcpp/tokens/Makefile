# $TenDRA$

.PATH : ${.CURDIR}

CFLAGS+=	-I${.CURDIR}/../src

TCC_OPTS+=	-yTENDRA_BASEDIR=${OBJ_PREFIX}/ \
		-Y${DEFAULT_BUILD} \
		-Yc++ \
		-Fj

DEPEND_SRC=	basic.j ptr_func.j ptr_mem.j throw.j vtable.j


basic.j: basic.cc
	${TCC} ${CFLAGS} ${TCC_OPTS} -o ${.TARGET} ${.ALLSRC}

throw.j: throw.cc
	${TCC} ${CFLAGS} ${TCC_OPTS} -o ${.TARGET} ${.ALLSRC}


CLEANFILES=	${DEPEND_SRC}

.include "../../../../mk/base/tendra.prog.mk"
