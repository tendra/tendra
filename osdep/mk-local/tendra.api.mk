# TenDRA make build infrastructure
#
# $Id$

.if !defined(_TENDRA_WORK_API_MK_)
_TENDRA_WORK_API_MK_=1

.include <tendra.base.mk>
.include <tendra.functions.mk>
.include <tendra.compiler.mk>
.include <tendra.situ.mk>

.if !exists(${PREFIX_TSPEC})
.BEGIN:
	@${ECHO} '$${PREFIX_TSPEC} must be installed'
	@${EXIT} 1;
.endif

# TODO: simplify this away
STARTUP_MACH=	${.CURDIR}/../startup

.if !exists(${STARTUP_MACH})
.BEGIN:
	@${ECHO} '$${STARTUP_MACH} must be present'
	@${EXIT} 1;
.endif


. if defined(OSVER)
CCOPTS+= -D_${OSVER}
. endif

. if defined(LIBCVER)
CCOPTS+= -D_${LIBCVER}
. endif



#
# Rules proper
#

JOPTS+= -Y32bit -D__BUILDING_LIBS

HACKS+=	-I${BASE_DIR}/machines/${OSFAM}/${BLDARCH}/include


.for api in ${APIS:R}

. if !exists(${PREFIX_TSPEC}/TenDRA/src/${api}.api)
.BEGIN:
	@${ECHO} '$${PREFIX_TSPEC}/TenDRA/src/${api}.api not found'
	@${EXIT} 1;
. endif


. if exists(${STARTUP_MACH}/${api}.h)
JOPTS${api}+=	-f${STARTUP_MACH}/${api}.h
. endif

APISRCS${api}!=	find ${PREFIX_TSPEC}/TenDRA/src/${api}.api -name '*.c'
APISRCS${api}:=	${APISRCS${api}:T}

. for src in ${APISRCS${api}}
${OBJ_SDIR}/apis/${api}.api/${src:R}.j: ${PREFIX_TSPEC}/TenDRA/src/${api}.api/${src}
	@${CONDCREATE} "${.TARGET:H}"
	@${ECHO} "==> Compiling ${api}.api/${src}"
	${TCC_IN_SITU} ${HACKS} ${TCCOPTS} ${CCOPTS} ${JOPTS} ${JOPTS${api}} \
		-I${PREFIX_TSPEC}/include/${api}.api \
		-o ${.TARGET} ${.ALLSRC} -Ymakelib

APIOBJS${api}+=	${OBJ_SDIR}/apis/${api}.api/${src:R}.j
. endfor


${OBJ_SDIR}/apis/${api}.tl: ${APIOBJS${api}}
	@${CONDCREATE} "${OBJ_SDIR}/apis"
	@${ECHO} "==> Linking ${api} API"
	${TLD} -mc -o ${.TARGET} ${.ALLSRC}



#
# User-facing targets
#

all:: ${OBJ_SDIR}/apis/${api}.tl


clean::
	${REMOVE} ${OBJ_SDIR}/apis/${api}.tl ${APIOBJS${api}}


install:: ${OBJ_SDIR}/apis/${api}.tl
	@${ECHO} "==> Installing ${api} API"
	@${CONDCREATE} "${PREFIX_API}"
	${INSTALL} -m 644 ${OBJ_SDIR}/apis/${api}.tl "${PREFIX_API}/${api}.tl"

.endfor


clean::


.endif	# !defined(_TENDRA_WORK_API_MK_)
