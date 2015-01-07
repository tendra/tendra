# $Id$

.include "Makefile.inc"


.include <tendra.base.mk>
.include <tendra.functions.mk>
.include <tendra.compiler.mk>


TPLSRCS+=	INT64b.tpl
TPLSRCS+=	abstract.tpl

TPLOPTS=	-I${.CURDIR}

.include <tendra.tpl.mk>


# TODO: i'm adding c.tl because of use of undefined token, ~comp_off
# but I don't think it belongs here. (INT64a.c uses it)
${OBJ_SDIR}/INT64.o: INT64a.c ${CAPSULES}
	${TCC} ${TCCOPTS} -c -o ${.TARGET} \
		-J${OBJ_SDIR} -jtarget_tok \
		-J${OBJ_SDIR} -jc \
		-M -WP,-I. ${.ALLSRC}

OBJS+=	${OBJ_SDIR}/INT64.o


LIB=		tsl
EXEC_LIB=	${PREFIX_SYS}

.include <tendra.lib.mk>



clean::
	${RMFILE} ${OBJS}

