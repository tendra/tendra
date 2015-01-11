# $Id: Makefile 3511 2015-01-09 14:10:09Z kate $

.include "Makefile.inc"


.include <tendra.base.mk>
.include <tendra.functions.mk>
.include <tendra.compiler.mk>


TPLSRCS+= tdfc2.tpl
TPLSRCS+= tcpplus.tpl

.include <tendra.tpl.mk>


.for prod in ${CAPSULES:T:R}
${OBJ_SDIR}/${prod}.tl: ${OBJ_SDIR}/${prod}.j
	@${CONDCREATE} "${OBJ_SDIR}"
	@${ECHO} "==> Linking ${WRKDIR}/${.TARGET:T}"
	${TLD} -mc ${TLDOPTS} -o ${.TARGET} ${.ALLSRC}
.endfor


#
# User-facing targets
#

.for prod in ${CAPSULES:T:R}
all:: ${OBJ_SDIR}/${prod}.tl
.endfor


clean::
.for prod in ${CAPSULES:T:R}
	${RMFILE} ${OBJ_SDIR}/${prod}.tl
.endfor


.for prod in ${CAPSULES:T:R}
install:: ${OBJ_SDIR}/${prod}.tl
	@${ECHO} "==> Installing ${prod} LPI"
	@${CONDCREATE} "${PREFIX_LPI}"
	${INSTALL} -m 644 ${OBJ_SDIR}/${prod}.tl "${PREFIX_LPI}/${prod}.tl"
.endfor

