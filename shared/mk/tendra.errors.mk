# TenDRA make build infrastructure
#
# $Id$

.if !defined(_TENDRA_WORK_ERRORS_MK_)
_TENDRA_WORK_ERRORS_MK_=1

.include <tendra.base.mk>
.include <tendra.functions.mk>

.if !defined(ERRORS)
.BEGIN:
	@${ECHO} '$${ERRORS} must be set'
	@${EXIT} 1;
.endif


${ERROR_DECL}: ${ERRORS}
	@${ECHO} "==> Translating ${WRKDIR}/${ERROR_DECL}"
	${CAT} ${.ALLSRC} | ${MAKE_ERR} > ${.TARGET} \
		|| ( ${REMOVE} ${.TARGET}; ${EXIT} 1 )

${ERROR_DECLX}: ${ERRORS} ${ERRORSX}
	@${ECHO} "==> Translating ${WRKDIR}/${ERROR_DECLX}"
	${CAT} ${.ALLSRC} | ${MAKE_ERR} > ${.TARGET} \
		|| ( ${REMOVE} ${.TARGET}; ${EXIT} 1 )

${ERROR_DEFN}: ${ERRORS} ${ERRORSX}
	@${ECHO} "==> Translating ${WRKDIR}/${ERROR_DEFN}"
	${CAT} ${.ALLSRC} | ${MAKE_ERR} -d > ${.TARGET} \
		|| ( ${REMOVE} ${.TARGET}; ${EXIT} 1 )

${ERROR_USAGE}: ${ERRORS}
	@${ECHO} "==> Translating ${WRKDIR}/${ERROR_USAGE}"
	${CAT} ${.ALLSRC} | ${MAKE_ERR} -u > ${.TARGET} \
		|| ( ${REMOVE} ${.TARGET}; ${EXIT} 1 )



#
# User-facing targets
#

regen:: ${ERROR_DECL} ${ERROR_DECLX} ${ERROR_DEFN} ${ERROR_USAGE}


regen-clean::
	${REMOVE} ${ERROR_DECL} ${ERROR_DECLX} ${ERROR_DEFN} ${ERROR_USAGE}


install::



.endif	# !defined(_TENDRA_WORK_ERROR_MK_)
