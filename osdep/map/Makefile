# $Id: Makefile 3511 2015-01-09 14:10:09Z kate $

.include "Makefile.inc"


.include <tendra.base.mk>
.include <tendra.functions.mk>
.include <tendra.compiler.mk>


TPLSRCS+= c.tpl
TPLSRCS+= f.tpl

.include <tendra.tpl.mk>


.for map in ${CAPSULES:T:R}
${OBJ_SDIR}/${map}.tl: ${OBJ_SDIR}/${map}.j
	@${CONDCREATE} "${OBJ_SDIR}"
	@${ECHO} "==> Linking ${WRKDIR}/${.TARGET:T}"
	${TLD} -mc ${TLDOPTS} -o ${.TARGET} ${.ALLSRC}
.endfor


#
# User-facing targets
#

.for map in ${CAPSULES:T:R}
all:: ${OBJ_SDIR}/${map}.tl
.endfor


clean::
.for map in ${CAPSULES:T:R}
	${RMFILE} ${OBJ_SDIR}/${map}.tl
.endfor


.for map in ${CAPSULES:T:R}
install:: ${OBJ_SDIR}/${map}.tl
	@${ECHO} "==> Installing ${map} language mapping"
	@${CONDCREATE} "${PREFIX_MAP}"
	${INSTALL} -m 644 ${OBJ_SDIR}/${map}.tl "${PREFIX_MAP}/${map}.tl"
.endfor

