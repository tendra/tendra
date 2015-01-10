# $Id$

.include "Makefile.inc"


.include <tendra.base.mk>
.include <tendra.functions.mk>
.include <tendra.compiler.mk>


TPLSRCS+=	INT64b.tpl
TPLSRCS+=	abstract.tpl

TPLOPTS=	-I${.CURDIR}

.include <tendra.tpl.mk>


${OBJ_SDIR}/INT64a.j: INT64a.c
	@${CONDCREATE} "${OBJ_SDIR}"
	@${ECHO} "==> Compiling ${.ALLSRC}"
	${TCC} ${TCCOPTS} -Fj -o ${.TARGET} \
		${.ALLSRC}

CAPSULES += ${OBJ_SDIR}/INT64a.j
CAPSULES += ${OBJ_SDIR}/sys_toks.j


${OBJ_SDIR}/INT64.o: ${CAPSULES}
	${TCC} ${TCCOPTS} -c -o ${.TARGET} \
		-J${OBJ_SDIR} -jc -jmap_c  \
		-M -WP,-I. ${.ALLSRC}

OBJS+=	${OBJ_SDIR}/INT64.o


LIB=		tsl
EXEC_LIB=	${PREFIX_SYS}

.include <tendra.lib.mk>



clean::
	${RMFILE} ${OBJS}

