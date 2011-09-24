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
		|| ( ${RMFILE} ${.TARGET}; ${EXIT} 1 )

${ERROR_DEFN}: ${ERRORS}
	@${ECHO} "==> Translating ${WRKDIR}/${ERROR_DEFN}"
	${CAT} ${.ALLSRC} | ${MAKE_ERR} -d > ${.TARGET} \
		|| ( ${RMFILE} ${.TARGET}; ${EXIT} 1 )

${ERROR_USAGE}: ${ERRORS}
	@${ECHO} "==> Translating ${WRKDIR}/${ERROR_USAGE}"
	${CAT} ${.ALLSRC} | ${MAKE_ERR} -u > ${.TARGET} \
		|| ( ${RMFILE} ${.TARGET}; ${EXIT} 1 )



#
# User-facing targets
#

regen:: ${ERROR_DECL} ${ERROR_DEFN} ${ERROR_USAGE}


regen-clean::
	${RMFILE} ${ERROR_DECL} ${ERROR_DEFN} ${ERROR_USAGE}


install::



.endif	# !defined(_TENDRA_WORK_ERROR_MK_)
