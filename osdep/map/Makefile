# $Id: Makefile 3511 2015-01-09 14:10:09Z kate $

.include "Makefile.inc"


.include <tendra.base.mk>
.include <tendra.functions.mk>
.include <tendra.compiler.mk>


TPLSRCS+= c.tpl
TPLSRCS+= f.tpl
TPLSRCS+= tdf.tpl

.include <tendra.tpl.mk>


.for map in ${CAPSULES:T:R}
${OBJ_SDIR}/${map}.tl: ${OBJ_SDIR}/${map}.j
	@${CONDCREATE} "${OBJ_SDIR}"
	@${ECHO} "==> Linking ${WRKDIR}/${.TARGET:T}"
	${TLD} -mc ${TLDOPTS} -o ${.TARGET} ${.ALLSRC}
.endfor


#
# Internal targets (for use by libtsl)
#

${OBJ_DIR}/src/map_c.tl: ${OBJ_SDIR}/c.tl
	@${ECHO} "==> Symlinking for libtsl use"
	@${CONDCREATE} "${OBJ_DIR}/src"
	${LN} -s ${.ALLSRC} ${.TARGET}


#
# User-facing targets
#

.for map in ${CAPSULES:T:R}
all:: ${OBJ_SDIR}/${map}.tl
.endfor


clean::
	${RMFILE} ${OBJ_DIR}/src/map_c.tl
.for map in ${CAPSULES:T:R}
	${RMFILE} ${OBJ_SDIR}/${map}.tl
.endfor


install:: ${OBJ_DIR}/src/map_c.tl

.for map in ${CAPSULES:T:R}
install:: ${OBJ_SDIR}/${map}.tl
	@${ECHO} "==> Installing ${map} language mapping"
	@${CONDCREATE} "${PREFIX_MAP}"
	${INSTALL} -m 644 ${OBJ_SDIR}/${map}.tl "${PREFIX_MAP}/${map}.tl"
.endfor

