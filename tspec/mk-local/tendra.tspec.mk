# $Id$

# Copyright 2010-2011, The TenDRA Project.
#
# See doc/copyright/ for the full copyright terms.


.if !defined(_TENDRA_WORK_TSPEC_MK_)
_TENDRA_WORK_TSPEC_MK_=1

.include <tendra.base.mk>
.include <tendra.functions.mk>



TSPEC_TIOUT=	${OBJ_DIR}/share/TenDRA/include
TSPEC_TSOUT=	${OBJ_DIR}/share/TenDRA/src

TSPEC_FLAGS+=	-O${TSPEC_TIOUT}
TSPEC_FLAGS+=	-S${TSPEC_TSOUT}


.for api in ${APIS}
${TSPEC_TIOUT}/${api}.api ${TSPEC_TSOUT}/${api}.api: ${TSPEC}
	@${ECHO} "==> Creating base API source for ${api}"
	${TSPEC} ${TSPEC_FLAGS} -I${BASE_DIR}/base -b ${api}
.endfor



#
# User-facing targets
#

all:: ${TSPEC} ${APIS:S/^/${TSPEC_TIOUT}\//g:S/$/.api/g} \
               ${APIS:S/^/${TSPEC_TSOUT}\//g:S/$/.api/g}


clean::


install:: all
	@${CONDCREATE} "${PREFIX_SHARE}/tspec"
	${INSTALL} -m 755 -d ${PREFIX_SHARE}/tspec
	${COPY} -R ${OBJ_DIR}/share/TenDRA ${PREFIX_SHARE}/tspec



.endif	# !defined(_TENDRA_WORK_TSPEC_MK_)
