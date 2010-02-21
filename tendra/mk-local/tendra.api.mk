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



#
# External dependencies
#

${OBJ_DIR}/${TOKENS_COMMON}/c_toks.j:
	@cd ${BASE_DIR}/${TOKENS_MACH} && ${MAKE} ${.TARGET}

${OBJ_DIR}/${TOKENS_MACH}/sys.j:
	@cd ${BASE_DIR}/${TOKENS_MACH} && ${MAKE} ${.TARGET}



#
# Rules proper
#

# XXX: don't hardcode /usr/include. have it appended per machines/ instead
JOPTS= -Y32bit -I${BASE_DIR}/src/lib/machines/${OSFAM}/${BLDARCH}/include \
	-I/usr/include -D__BUILDING_LIBS


# TODO: need to do this for all APIs
TSPECAPIS!=	find ${TSPEC_PREFIX}/src -type d -name '*.api'
TSPECAPIS:=	${TSPECAPIS:C/^${TSPEC_PREFIX}\/src\///g}

.for api in ${TSPECAPIS:R}

. if exists(${BASE_DIR}/${STARTUP_MACH}/${api:R}.h)
JOPTS${api}+=	-f${BASE_DIR}/${STARTUP_MACH}/${api:R}.h
. endif

APISRCS${api}!=	ls -1 ${TSPEC_PREFIX}/src/${api}.api; echo

. for src in ${APISRCS${api}}
${OBJ_DIR}/${APIS}/${api}.api/${src:R}.j: ${TSPEC_PREFIX}/src/${api}.api/${src}
	@${CONDCREATE} "${.TARGET:H}"
	@${ECHO} "==> Compiling ${api}.api/${src}"
	${TCC} ${TCCOPTS} ${CCOPTS} ${JOPTS} ${JOPTS${api}} \
		-I${TSPEC_PREFIX}/include/${api}.api \
		-o ${.TARGET} ${.ALLSRC} -Ymakelib

APIOBJS${api}+=	${OBJ_DIR}/${APIS}/${api}.api/${src:R}.j
. endfor


# TODO: For the moment, I'm linking sys.j in with each ${api:R}.tl (per API).
# However, since sys.j is not specific to each API (rather, it is specific to
# each producer's language), I think it makes more sense to install this as a
# separate .tl library, and to have tld explicitly link against it, along with
# linking against an API. I think this is what was done historically, since
# lib/machines/README from the 4.1.2 release mentions "This gives a capsule
# sys.j which defines the producer interface. This capsule is linked into the
# C producer TDF library, c.tl." Careful to avoid name clashes with APIs;
# perhaps we should have a directory just for "producer interface" libraries.
# Is this also used by C++?
${OBJ_DIR}/${APIS}/${api}.tl: ${OBJ_DIR}/${TOKENS_MACH}/sys.j


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
	@{CONDCREATE} "${INSTALL_DIR}/lib"
	${INSTALL} -m 644 ${OBJ_DIR}/${APIS}/${api}.tl "${INSTALL_DIR}/lib"

.endfor


clean::
	@cd ${BASE_DIR}/${TOKENS_MACH} && ${MAKE} clean


.endif	# !defined(_TENDRA_WORK_API_MK_)
