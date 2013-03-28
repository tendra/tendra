# $Id$

# Copyright 2012, The TenDRA Project.
#
# See doc/copyright/ for the full copyright terms.

.if !defined(_TENDRA_WORK_TDFTEST_MK_)
_TENDRA_WORK_TDFTEST_MK=1

.include <tendra.base.mk>
.include <tendra.functions.mk>
.include <tendra.compiler.mk>


.if !defined(TCC)
.BEGIN:
	@${ECHO} '$${TCC} must be set'
	@${EXIT} 1;
.endif

.if !defined(TESTS)
.BEGIN:
	@${ECHO} '$${TESTS} must be set'
	@${EXIT} 1;
.endif


.for test in ${TESTS}
${OBJ_SDIR}/${test:R}: ${test}
	@${CONDCREATE} "${OBJ_SDIR}"
	@${ECHO} "==> Translating ${WRKDIR}/${.ALLSRC}"
	${TCC} -Ytnc -o ${.TARGET} ${.ALLSRC}
.endfor


#
# User-facing targets
#

.for test in ${TESTS}
test:: ${OBJ_SDIR}/${test:R}
	@${ECHO} "==> Testing ${WRKDIR}/${test:R}"
	${OBJ_SDIR}/${test:R} || ${ECHO} XXX
.endfor


.for test in ${TESTS}
all:: ${OBJ_SDIR}/${test:R}
.endfor


clean::
.for test in ${TESTS}
	${RMFILE} ${OBJ_SDIR}/${test:R}
.endfor


install::


.endif  # !defined(_TENDRA_WORK_TDFTEST_MK_)

