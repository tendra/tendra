# TenDRA make build infrastructure
#
# $Id$

.if !defined(_TENDRA_WORK_LIB_MK_)
_TENDRA_WORK_LIB_MK_=1

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



lib${LIB}.a: ${OBJS}
	${AR} cr ${.TARGET} ${OBJS}
	${RANLIB} ${.TARGET}

CLEAN_EXTRA+=	lib${LIB}.a ${OBJS}
_objdir=	${OBJ_SDIR}



#
# User-facing targets
#

all:: lib${LIB}.a


clean::
. if "${CLEAN_EXTRA}" != ""
	${REMOVE} ${CLEAN_EXTRA}
. endif


install::
	@${ECHO} "==> Installing lib${LIB}.a"
	${CONDCREATE} "${COMMON_DIR}/sys"
	${INSTALL} -m 755 lib${LIB}.a ${COMMON_DIR}/sys/lib${LIB}.a



.endif	# !defined(_TENDRA_WORK_LIB_MK_)
