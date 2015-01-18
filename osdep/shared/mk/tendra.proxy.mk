# $Id$

# Copyright 2010-2011, The TenDRA Project.
#
# See doc/copyright/ for the full copyright terms.


.if !defined(_TENDRA_WORK_PROXY_MK_)
_TENDRA_WORK_PROXY_MK_=1

.include <tendra.base.mk>
.include <tendra.functions.mk>


.if !defined(PROXY)
.BEGIN:
	@${ECHO} '$${PROXY} must be set'
	@${EXIT} 1;
.endif


#
# Rules proper
#

.for proxy in ${PROXY}
${OBJ_SDIR}/${proxy}.j: ${BASE_DIR}/proxy/tdf/${proxy}.tpl
	@${CONDCREATE} "${OBJ_SDIR}"
	@${ECHO} "==> Translating proxy/${.TARGET:T}"
	${TPL} ${.ALLSRC} ${.TARGET}
.endfor


#
# User-facing targets
#

all::


clean::
.for proxy in ${PROXY}
	${RMFILE} ${OBJ_SDIR}/${proxy}.j
.endfor


install::


.endif	# !defined(_TENDRA_WORK_PROXY_MK_)
