# Copyright 2010-2011, The TenDRA Project.
#
# See doc/copyright/ for the full copyright terms.


.if !defined(_TENDRA_WORK_FEATURE_MK_)
_TENDRA_WORK_FEATURE_MK_=1

.include <tendra.base.mk>
.include <tendra.functions.mk>

.if !defined(HEADERS)
.BEGIN:
	@${ECHO} '$${HEADERS} must be set'
	@${EXIT} 1;
.endif



#
# User-facing targets
#

all::


clean::


install::
	@${CONDCREATE} "${PREFIX_TSPEC}/TenDRA/feature"
	@${ECHO} "==> Installing feature selection headers"
.for header in ${HEADERS}
	${INSTALL} -m 644 ${header} ${PREFIX_TSPEC}/TenDRA/feature
.endfor


.endif	# !defined(_TENDRA_WORK_FEATURE_MK_)
