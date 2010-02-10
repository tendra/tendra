# $Id$

.include "Makefile.inc"


TPLSRCS=	INT64b.tpl abstract.tpl
TPLOPTS=	-I${.CURDIR}

.include <tendra.tpl.mk>


${OBJ_SDIR}/INT64a.j: INT64a.c
	${TCC} -Fj ${CFLAGS} ${TCCOPTS} -c -o ${.TARGET} ${.ALLSRC}

${OBJ_SDIR}/INT64a.o: ${OBJ_SDIR}/INT64a.j ${CAPSULES}
	${TCC} -c -o ${.TARGET} -jtarget_tok -M ${.ALLSRC}

OBJS=	${OBJ_SDIR}/INT64a.o


SRCS=	version.c

.include <tendra.obj.mk>


LIB=	tdf

.include <tendra.lib.mk>



clean::
	${REMOVE} ${OBJ_SDIR}/INT64a.o

