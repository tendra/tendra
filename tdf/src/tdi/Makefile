# $Id$

.include "Makefile.inc"


.include <tendra.base.mk>
.include <tendra.functions.mk>
.include <tendra.compiler.mk>


TPLSRCS+= except.tpl
TPLSRCS+= va.tpl

.include <tendra.tpl.mk>


.for tdi in ${CAPSULES:T:R}
${OBJ_SDIR}/tdi.tl: ${OBJ_SDIR}/${tdi}.j
.endfor

${OBJ_SDIR}/tdi.tl:
	@${CONDCREATE} "${OBJ_SDIR}"
	@${ECHO} "==> Linking ${WRKDIR}/${.TARGET:T}"
	${TLD} -mc ${TLDOPTS} -o ${.TARGET} ${.ALLSRC}


#
# User-facing targets
#

all:: ${OBJ_SDIR}/tdi.tl


clean::


install:: ${OBJ_SDIR}/tdi.tl
	@${ECHO} "==> Installing target dependent tokens"
	@${CONDCREATE} "${PREFIX_SYS}"
	${INSTALL} -m 644 ${OBJ_SDIR}/tdi.tl "${PREFIX_SYS}/tdi.tl"

