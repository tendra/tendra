# TenDRA make build infrastructure
#
# $Id$

.if !defined(_TENDRA_WORK_API_MK_)
_TENDRA_WORK_API_MK_=1

.include <tendra.base.mk>
.include <tendra.functions.mk>
.include <tendra.compiler.mk>

.if !exists(${TSPEC_PREFIX})
.BEGIN:
	@${ECHO} '$${TSPEC_PREFIX} must be installed'
	@${EXIT} 1;
.endif

# TODO: simplify this away
STARTUP_MACH=	${.CURDIR}/startup

.if !exists(${STARTUP_MACH})
.BEGIN:
	@${ECHO} '$${STARTUP_MACH} must be present'
	@${EXIT} 1;
.endif




#
# Rules proper
#

# XXX: don't hardcode /usr/include. have it appended per machines/ instead
JOPTS= -Y32bit -I${BASE_DIR}/src/lib/machines/${OSFAM}/${BLDARCH}/include \
	-I/usr/include -D__BUILDING_LIBS


.for api in ${APIS:R}

. if !exists(${TSPEC_PREFIX}/src/${api}.api)
.BEGIN:
	@${ECHO} '$${TSPEC_PREFIX}/src/${api}.api not found'
	@${EXIT} 1;
. endif


. if exists(${STARTUP_MACH}/${api}.h)
JOPTS${api}+=	-f${STARTUP_MACH}/${api}.h
. endif

APISRCS${api}!=	find ${TSPEC_PREFIX}/src/${api}.api -name '*.c'
APISRCS${api}:=	${APISRCS${api}:T}

. for src in ${APISRCS${api}}
${OBJ_DIR}/${APIS}/${api}.api/${src:R}.j: ${TSPEC_PREFIX}/src/${api}.api/${src}
	@${CONDCREATE} "${.TARGET:H}"
	@${ECHO} "==> Compiling ${api}.api/${src}"
	${TCC} ${TCCOPTS} ${CCOPTS} ${JOPTS} ${JOPTS${api}} \
		-I${TSPEC_PREFIX}/include/${api}.api \
		-o ${.TARGET} ${.ALLSRC} -Ymakelib

APIOBJS${api}+=	${OBJ_DIR}/${APIS}/${api}.api/${src:R}.j
. endfor


${OBJ_DIR}/${APIS}/${api}.tl: ${APIOBJS${api}}
	@${CONDCREATE} "${OBJ_DIR}/${APIS}"
	@${ECHO} "==> Linking ${api} API"
	${TLD} -mc -o ${.TARGET} ${.ALLSRC}



#
# User-facing targets
#

all:: ${OBJ_DIR}/${APIS}/${api}.tl


clean::
	${REMOVE} ${OBJ_DIR}/${APIS}/${api}.tl ${APIOBJS${api}}


install:: ${OBJ_DIR}/${APIS}/${api}.tl
	@${ECHO} "==> Installing ${API} API"
	@${CONDCREATE} "${INSTALL_DIR}/lib"
	${INSTALL} -m 644 ${OBJ_DIR}/${APIS}/${api}.tl "${INSTALL_DIR}/lib"

.endfor


clean::


.endif	# !defined(_TENDRA_WORK_API_MK_)
