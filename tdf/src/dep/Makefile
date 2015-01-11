# $Id$

.include "Makefile.inc"


.include <tendra.base.mk>
.include <tendra.functions.mk>
.include <tendra.compiler.mk>


TPLSRCS+= int.tpl
TPLSRCS+= pun.tpl

.include <tendra.tpl.mk>


.for dep in ${CAPSULES:T:R}
${OBJ_SDIR}/dep.tl: ${OBJ_SDIR}/${dep}.j
.endfor

${OBJ_SDIR}/dep.tl:
	@${CONDCREATE} "${OBJ_SDIR}"
	@${ECHO} "==> Linking ${WRKDIR}/${.TARGET:T}"
	${TLD} -mc ${TLDOPTS} -o ${.TARGET} ${.ALLSRC}


#
# User-facing targets
#

all:: ${OBJ_SDIR}/dep.tl


clean::


install:: ${OBJ_SDIR}/dep.tl
	@${ECHO} "==> Installing target dependent mapping"
	@${CONDCREATE} "${PREFIX_SYS}"
	${INSTALL} -m 644 ${OBJ_SDIR}/dep.tl "${PREFIX_SYS}/dep.tl"

