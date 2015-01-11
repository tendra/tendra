# $Id$

.include "Makefile.inc"


.include <tendra.base.mk>
.include <tendra.functions.mk>
.include <tendra.compiler.mk>


TPLSRCS+=	int64b.tpl
TPLSRCS+=	abstract.tpl

TPLOPTS=	-I${.CURDIR}

.include <tendra.tpl.mk>


${OBJ_SDIR}/int64a.j: int64a.c
	@${CONDCREATE} "${OBJ_SDIR}"
	@${ECHO} "==> Compiling ${.ALLSRC}"
	${TCC} ${TCCOPTS} -Fj -o ${.TARGET} \
		${.ALLSRC}

CAPSULES += ${OBJ_SDIR}/int64a.j


${OBJ_SDIR}/int64.o: ${CAPSULES}
	${TCC} ${TCCOPTS} -c -o ${.TARGET}  \
	    -J${PREFIX_MAP} -jc             \
	    -J${PREFIX_LPI} -jtdfc2         \
	    -J${PREFIX_SYS} -jabi -jdep     \
	    -M -WP,-I. ${.ALLSRC}

OBJS+=	${OBJ_SDIR}/int64.o


LIB=		int64
EXEC_LIB=	${PREFIX_SYS}

.include <tendra.lib.mk>



clean::
	${RMFILE} ${OBJS}

