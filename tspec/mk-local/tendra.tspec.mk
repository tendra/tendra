# TenDRA make build infrastructure
#
# $Id$

.if !defined(_TENDRA_WORK_TSPEC_MK_)
_TENDRA_WORK_TSPEC_MK_=1

.include <tendra.base.mk>
.include <tendra.functions.mk>



TSPEC_FLAGS+=	-O${OBJ_DIR}/share/TenDRA/include
TSPEC_FLAGS+=	-S${OBJ_DIR}/share/TenDRA/src


#
# User-facing targets
#

all:: ${TSPEC}
.for api in ${BASE_APIS}
	@${ECHO} "==> Creating API source for ${api}"
	${TSPEC} ${TSPEC_FLAGS} -I${BASE_DIR}/base ${api}
.endfor
.for api in ${EXT_APIS}
	@${ECHO} "==> Creating API source for ${api}"
	${TSPEC} ${TSPEC_FLAGS} -I${BASE_DIR}/base -I${BASE_DIR}/extension ${api}
.endfor


clean::


# TODO: dependencies
# TODO: output makefiles?
install::
	@${CONDCREATE} "${SHARE_DIR}/tspec"
	${INSTALL} -m 755 -d ${SHARE_DIR}/tspec
	${COPY} -R ${OBJ_DIR}/share/TenDRA ${SHARE_DIR}/tspec



.endif	# !defined(_TENDRA_WORK_TSPEC_MK_)
