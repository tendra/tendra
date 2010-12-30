# TenDRA make build infrastructure
#
# $Id$

.if !defined(_TENDRA_WORK_ENV_MK_)
_TENDRA_WORK_ENV_MK_=1

.include <tendra.base.mk>
.include <tendra.functions.mk>

.if !defined(ENVFILE) && !defined(ENVEXTRA)
.BEGIN:
	@${ECHO} '$${ENVFILE} or ${{ENVEXTRA} must be set'
	@${EXIT} 1;
.endif



${OBJ_DIR}/fixenv.sed:
	@${CONDCREATE} "${OBJ_DIR}"
	@${ECHO} "==> Creating ${.TARGET}"
	@${ECHO} "1,\$$s%-MACH-%${OSFAM}/${BLDARCH}%g"  > ${.TARGET}
	@${ECHO} "1,\$$s%-BLDARCH-%${BLDARCH}%g"       >> ${.TARGET}
	@${ECHO} "1,\$$s%-OSFAM-%${OSFAM}%g"           >> ${.TARGET}
	@${ECHO} "1,\$$s%-ENVDIR-%${PREFIX_ENV}%g"     >> ${.TARGET}
	@${ECHO} "1,\$$s%-TMPDIR-%${PREFIX_TMP}%g"     >> ${.TARGET}


${OBJ_SDIR}/env: ${OBJ_DIR}/fixenv.sed
	@${CONDCREATE} "${OBJ_DIR}/env"
	@${CONDCREATE} "${OBJ_SDIR}"
.for dir in ${ENVCOMMON}
	cd ${BASE_DIR}/${dir}; ${MAKE} ${OBJ_DIR}/${dir}/env
.endfor
.if defined(ENVFILE)
	@${ECHO} "==> Setting paths for ${WRKDIR} environments"
.endif
.for env in ${ENVFILE}
	sed -f ${OBJ_DIR}/fixenv.sed ${env} > ${OBJ_DIR}/env/${env}
.endfor
.for env in ${ENVEXTRA}
	# TODO: show 'extra' comment here
	${ECHO} '/* ${WRKDIR}/${env}: */'   >> ${OBJ_DIR}/env/${env:R}
	${ECHO}                             >> ${OBJ_DIR}/env/${env:R}
	sed -f ${OBJ_DIR}/fixenv.sed ${env} >> ${OBJ_DIR}/env/${env:R}
	${ECHO}                             >> ${OBJ_DIR}/env/${env:R}
.endfor
	@${ECHO} done > ${.TARGET}



#
# User-facing targets
#

all:: ${OBJ_SDIR}/env


clean::
.for dir in ${ENVCOMMON}
	cd ${BASE_DIR}/${dir}; ${MAKE} clean
.endfor
	${REMOVE} ${ENVFILE:C/^/${OBJ_DIR}\/env\//} ${ENVEXTRA:R:C/^/${OBJ_DIR}\/env\//}


install:: ${OBJ_SDIR}/env
	@${ECHO} "==> Installing ${WRKDIR} environments"
	@${CONDCREATE} "${PREFIX_ENV}"
.for env in ${ENVFILE}
	${INSTALL} -m 644 ${OBJ_DIR}/env/${env} ${PREFIX_ENV}/${env}
.endfor



.endif	# !defined(_TENDRA_WORK_ENV_MK_)
