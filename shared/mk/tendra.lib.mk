# $Id$

# Copyright 2004-2011, The TenDRA Project.
#
# See doc/copyright/ for the full copyright terms.


.if !defined(_TENDRA_LIB_MK_)
_TENDRA_LIB_MK_=1

.include <tendra.base.mk>
.include <tendra.functions.mk>

.if !defined(OBJS)
.BEGIN:
	@${ECHO} '$${OBJS} must be set'
	@${EXIT} 1;
.endif

.if !defined(LIB)
.BEGIN:
	@${ECHO} '$${LIB} must be set'
	@${EXIT} 1;
.endif


EXEC_LIB?=	${PREFIX_LIB}


${OBJ_SDIR}/lib${LIB}.a: ${OBJS}
	@${CONDCREATE} "${OBJ_SDIR}"
	@${ECHO} "==> Archiving ${WRKDIR}/${LIB}"
	${AR} cr ${.TARGET} ${.ALLSRC}
	${RANLIB} ${.TARGET}



#
# User-facing targets
#

all:: ${OBJ_SDIR}/lib${LIB}.a


clean::
	${RMFILE} ${OBJ_SDIR}/lib${LIB}.a


install:: all
	@${ECHO} "==> Installing ${WRKDIR}/lib${LIB}"
	@${CONDCREATE} "${EXEC_LIB}"
	${INSTALL} -m 755 ${OBJ_SDIR}/lib${LIB}.a ${EXEC_LIB}/lib${LIB}.a



.endif
