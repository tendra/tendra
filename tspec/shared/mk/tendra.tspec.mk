# $Id$

# Copyright 2010-2011, The TenDRA Project.
#
# See doc/copyright/ for the full copyright terms.


.if !defined(_TENDRA_WORK_TSPEC_MK_)
_TENDRA_WORK_TSPEC_MK_=1

.include <tendra.base.mk>
.include <tendra.functions.mk>



TSPEC_TOUT?=	${OBJ_DIR}/share/TenDRA

TSPEC_TFLAGS+=	-O${TSPEC_TOUT}
TSPEC_EFLAGS+=	-O${TSPEC_TOUT}


.for api in ${APIS}
${TSPEC_TOUT}/include/${api}.api ${TSPEC_TOUT}/src/${api}.api: ${TSPEC}
	@${ECHO} "==> Creating API source for ${api}"
	${TSPEC} ${TSPEC_TFLAGS} -I${BASE_DIR}/base -b ${api}
.endfor

.for api in ${APIS}
${TSPEC_TOUT}/env/${api}: ${TSPEC}
	@${ECHO} "==> Creating tcc environment for ${api}"
	${TSPEC} ${TSPEC_EFLAGS} -I${BASE_DIR}/base -b -y ${api}
.endfor



#
# User-facing targets
#

all:: ${TSPEC} ${APIS:S/^/${TSPEC_TOUT}\/include\//g:S/$/.api/g} \
               ${APIS:S/^/${TSPEC_TOUT}\/src\//g:S/$/.api/g} \
               ${APIS:S/^/${TSPEC_TOUT}\/env\//g}


clean::


install:: all
	@${CONDCREATE} "${PREFIX_SHARE}/tspec"
	${INSTALL} -m 755 -d ${PREFIX_SHARE}/tspec
	${COPY} -R ${OBJ_DIR}/share/TenDRA ${PREFIX_SHARE}/tspec



.endif	# !defined(_TENDRA_WORK_TSPEC_MK_)
