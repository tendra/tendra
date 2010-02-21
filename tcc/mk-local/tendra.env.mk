# TenDRA make build infrastructure
#
# $Id$

.if !defined(_TENDRA_WORK_ENV_MK_)
_TENDRA_WORK_ENV_MK_=1

.include <tendra.base.mk>
.include <tendra.functions.mk>

.if !defined(ENVFILE)
.BEGIN:
	@${ECHO} '$${ENVFILE} must be set'
	@${EXIT} 1;
.endif



${OBJ_DIR}/fixenv.sed:
	@${ECHO} "==> Creating ${.TARGET}"
	@${ECHO} "1,\$$s%-MACH-%${OSFAM}/${BLDARCH}%g"          > ${.TARGET}
	@${ECHO} "1,\$$s%-BLDARCH-%${BLDARCH}%g"               >> ${.TARGET}
	@${ECHO} "1,\$$s%-OSFAM-%${OSFAM}%g"                   >> ${.TARGET}
	@${ECHO} "1,\$$s%-MACHDIR-%${MACH_BASE}%g"             >> ${.TARGET}
	@${ECHO} "1,\$$s%-BINDIR-%${MACH_BASE}/bin%g"          >> ${.TARGET}
	@${ECHO} "1,\$$s%-ENVDIR-%${PREFIX}/lib/tcc/env%g"     >> ${.TARGET}
	@${ECHO} "1,\$$s%-LIBDIR-%${MACH_BASE}/lib%g"          >> ${.TARGET}
	@${ECHO} "1,\$$s%-INCLDIR-%${COMMON_DIR}/include%g"    >> ${.TARGET}
	@${ECHO} "1,\$$s%-STARTUPDIR-%${COMMON_DIR}/startup%g" >> ${.TARGET}
	@${ECHO} "1,\$$s%-TMPDIR-%${TMP_DIR}%g"                >> ${.TARGET}

.for entry in ${ENVFILE}
${OBJ_DIR}/env/${entry}: ${OBJ_DIR}/fixenv.sed ${entry}
	@${CONDCREATE} "${OBJ_DIR}/env"
	@${ECHO} "==> Setting paths for ${WRKDIR}/${entry} environment"
	sed -f ${OBJ_DIR}/fixenv.sed ${entry} > ${OBJ_DIR}/env/${entry}
.endfor

${OBJ_DIR}/env/_extra: ${OBJ_DIR}/env \
	${OBJ_DIR}/env/build ${OBJ_DIR}/env/default
.if "${ENVEXTRA}" != ""
	cat ${ENVEXTRA} >> ${OBJ_DIR}/env/build
	cat ${ENVEXTRA} >> ${OBJ_DIR}/env/default
.endif
	@touch ${OBJ_DIR}/env/_extra



#
# User-facing targets
#

all:: ${ENVFILE:C/^/${OBJ_DIR}\/env\//} ${OBJ_DIR}/env/_extra


clean::
	${REMOVE} ${ENVFILE:C/^/${OBJ_DIR}\/env\//}
	${REMOVE} ${OBJ_DIR}/env/_extra


install:: all
	@${ECHO} "==> Installing ${WRKDIR}/ ${ENVFILE} environments"
	@${CONDCREATE} "${PREFIX}/lib/tcc/env" ;
.for entry in ${ENVFILE}
	${INSTALL} -m 644 ${OBJ_DIR}/env/${entry} ${PREFIX}/lib/tcc/env/${entry}
.endfor



.endif	# !defined(_TENDRA_WORK_ENV_MK_)
