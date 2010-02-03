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



#
# Build environments.
#
fixenv.sed:
	@${ECHO} "==> Create ${.TARGET}"
	@${ECHO} "1,\$$s%-MACH-%${OSFAM}/${BLDARCH}%g" 		\
		> ${OBJ_DIR}/${.TARGET}
	@${ECHO} "1,\$$s%-BLDARCH-%${BLDARCH}%g" 		\
		>> ${OBJ_DIR}/${.TARGET}
	@${ECHO} "1,\$$s%-OSFAM-%${OSFAM}%g" 			\
		>> ${OBJ_DIR}/${.TARGET}
	@${ECHO} "1,\$$s%-MACHDIR-%${MACH_BASE}%g" 		\
		>> ${OBJ_DIR}/${.TARGET}
	@${ECHO} "1,\$$s%-BINDIR-%${MACH_BASE}/bin%g" 		\
		>> ${OBJ_DIR}/${.TARGET}
	@${ECHO} "1,\$$s%-ENVDIR-%${MACH_BASE}/env%g" 		\
		>> ${OBJ_DIR}/${.TARGET}
	@${ECHO} "1,\$$s%-LIBDIR-%${MACH_BASE}/lib%g" 		\
		>> ${OBJ_DIR}/${.TARGET}
	@${ECHO} "1,\$$s%-INCLDIR-%${COMMON_DIR}/include%g" 	\
		>> ${OBJ_DIR}/${.TARGET}
	@${ECHO} "1,\$$s%-STARTUPDIR-%${COMMON_DIR}/startup%g" 	\
		>> ${OBJ_DIR}/${.TARGET}
	@${ECHO} "1,\$$s%-TMPDIR-%${TMP_DIR}%g" 		\
		>> ${OBJ_DIR}/${.TARGET}

_REALWORK: fixenv.sed .USE
	@${ECHO} "==> Fixing paths for ${ENVFILE} environments"
. for entry in ${ENVFILE}
	sed -f ${OBJ_DIR}/fixenv.sed ${.CURDIR}/${entry} > ${OBJ_DIR}/${ENVIRONMENT}/${entry}
. endfor
. if "${ENVEXTRA}" != ""
	cat ${.CURDIR}/${ENVEXTRA} >> ${OBJ_DIR}/${ENVIRONMENT}/build
	cat ${.CURDIR}/${ENVEXTRA} >> ${OBJ_DIR}/${ENVIRONMENT}/default
. endif

_objdir=	${OBJ_DIR}/${ENVIRONMENT}



#
# Install environment(s).
#
_REALINSTALL: .USE
	@${ECHO} "==> Installing ${ENVFILE} environments"
	${CONDCREATE} "${MACH_BASE}/env" ;
. for entry in ${ENVFILE}
	${INSTALL} -m 644 ${.OBJDIR}/${entry} ${MACH_BASE}/env/${entry}
. endfor



.endif	# !defined(_TENDRA_WORK_ENV_MK_)
