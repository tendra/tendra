# TenDRA make suffix rules
#
# $Id$

.if !defined(_TENDRA_RULES_MK_)
_TENDRA_RULES_MK_=1

.include <tendra.base.mk>

PARTIMP=        ${.IMPSRC:C/^${BASE_DIR}\///1}

.SUFFIXES: .c .cc .sid .j

.c.j:
	@${ECHO} "==> Compiling ${PARTIMP}"
	${TCC} ${TCCOPTS} ${CCOPTS} ${JOPTS} -o ${.TARGET} ${.IMPSRC} -Ymakelib

.cc.j:
	@${ECHO} "==> Compiling ${PARTIMP}"
	${TCC} ${TXXOPTS} ${CCOPTS} ${JOPTS} -o ${.TARGET} ${.IMPSRC} -Ymakelib

.sid.c:
	@${ECHO} "==> Transforming ${PARTIMP} and ${PARTIMP:S/.sid/.act/}"
	${SID} ${SIDOPTS} ${.IMPSRC} ${.IMPSRC:S/.sid/.act/} ${.TARGET} \
		${.TARGET:S/.c/.h/}

.endif	# !defined(_TENDRA_RULES_MK_)
