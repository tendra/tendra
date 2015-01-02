# $Id$

# Copyright 2010-2011, The TenDRA Project.
#
# See doc/copyright/ for the full copyright terms.


.if !defined(_TENDRA_WORK_TSPEC_MK_)
_TENDRA_WORK_TSPEC_MK_=1

.include <tendra.base.mk>
.include <tendra.functions.mk>



TSPEC_TIOUT=	${OBJ_DIR}/share/TenDRA/include
TSPEC_TUOUT=	${OBJ_DIR}/share/TenDRA/subset
TSPEC_TSOUT=	${OBJ_DIR}/share/TenDRA/src
TSPEC_TEOUT=	${OBJ_DIR}/share/TenDRA/env

TSPEC_TFLAGS+=	-O${TSPEC_TIOUT}
TSPEC_TFLAGS+=	-U${TSPEC_TUOUT}
TSPEC_TFLAGS+=	-S${TSPEC_TSOUT}
TSPEC_EFLAGS+=	-E${TSPEC_TEOUT}


.for api in ${APIS}
${TSPEC_TIOUT}/${api}.api ${TSPEC_TSOUT}/${api}.api: ${TSPEC}
	@${ECHO} "==> Creating API source for ${api}"
	${TSPEC} ${TSPEC_TFLAGS} -I${BASE_DIR}/base -b ${api}
.endfor

.for api in ${APIS}
${TSPEC_TEOUT}/${api}: ${TSPEC}
	@${ECHO} "==> Creating tcc environment for ${api}"
	${TSPEC} ${TSPEC_EFLAGS} -I${BASE_DIR}/base -b -y ${api}
.endfor



#
# User-facing targets
#

all:: ${TSPEC} ${APIS:S/^/${TSPEC_TIOUT}\//g:S/$/.api/g} \
               ${APIS:S/^/${TSPEC_TSOUT}\//g:S/$/.api/g} \
               ${APIS:S/^/${TSPEC_TEOUT}\//g}


clean::


install:: all
	@${CONDCREATE} "${PREFIX_SHARE}/tspec"
	${INSTALL} -m 755 -d ${PREFIX_SHARE}/tspec
	${COPY} -R ${OBJ_DIR}/share/TenDRA ${PREFIX_SHARE}/tspec



.endif	# !defined(_TENDRA_WORK_TSPEC_MK_)
