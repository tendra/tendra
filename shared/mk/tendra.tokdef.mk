# TenDRA make build infrastructure
#
# $Id$

.if !defined(_TENDRA_WORK_TOKDEF_MK_)
_TENDRA_WORK_TOKDEF_MK_=1

.include <tendra.base.mk>
.include <tendra.functions.mk>

.if !defined(TDFLIB)
.BEGIN:
	@${ECHO} '$${TDFLIB} must be set'
	@${EXIT} 1;
.endif



#
# Build token definitions.
#
_REALWORK: .USE
	@${ECHO} "==> Building ${TDFLIB} token definitions"

_objdir=	${OBJ_SDIR}



#
# Install token definitions.
#
_REALINSTALL: .USE
	${INSTALL} -m 644 ${.OBJDIR}/${TDFLIB} ${INSTALL_DIR}/lib



.endif	# !defined(_TENDRA_WORK_TOKDEF_MK_)
