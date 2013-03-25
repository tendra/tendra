# $Id$

# Copyright 2010-2011, The TenDRA Project.
#
# See doc/copyright/ for the full copyright terms.


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


. if defined(OSVER)
CCOPTS+= -D_${OSVER}
. endif

. if defined(LIBCVER)
CCOPTS+= -D_${LIBCVER}
. endif

. if defined(BLDARCH)
CCOPTS+= -D_ARCH_${BLDARCH}
. endif


#
# Rules proper
#

JOPTS+= -Y32bit -D__BUILDING_LIBS

# The include order is important here; CPU-specific hacked includes need to
# be able to #include_next the more general includes in common/.
.if exists(${BASE_DIR}/libc/${OSFAM}/arch/${BLDARCH})
HACKS+=	-I${BASE_DIR}/libc/${OSFAM}/arch/${BLDARCH}
.endif

.if exists(${BASE_DIR}/libc/${OSFAM}/include)
HACKS+=	-I${BASE_DIR}/libc/${OSFAM}/include
.endif

.if defined(GLIBC_NAME)
. if exists(${BASE_DIR}/libc/${GLIBC_NAME:tl}/include)
HACKS+=	-I${BASE_DIR}/libc/${GLIBC_NAME:tl}/include
. endif
.endif


.if exists(${BASE_DIR}/libc/${OSFAM}/startup)
STARTUP_MACH+=	${BASE_DIR}/libc/${OSFAM}/startup
.endif

# TODO: hacky
UPPER=	ABCDEFGHIJKLMNOPQRSTUVWXYZ
LOWER=	abcdefghijklmnopqrstuvwxyz
GLIBC_DIR:=	${GLIBC_NAME:C/${UPPER}/${LOWER}/g}

.if defined(GLIBC_NAME)
. if exists(${BASE_DIR}/libc/${GLIBC_DIR:tl}/startup)
STARTUP_MACH+=	${BASE_DIR}/libc/${GLIBC_DIR:tl}/startup
. endif
.endif


.for api in ${APIS:R}

. if !exists(${PREFIX_TSPEC}/TenDRA/src/${api}.api)
.BEGIN:
	@${ECHO} '$${PREFIX_TSPEC}/TenDRA/src/${api}.api not found'
	@${EXIT} 1;
. endif


# for __WRONG definitions
. if exists(${.CURDIR}/${api}.h)
JOPTS${api}+=	-f${.CURDIR}/${api}.h
. endif

# These are included before ${STARTUP_MACH}/${api}.h so that the hacked includes
# may #undef or override them if neccessary.
. if exists(${PREFIX_TSPEC}/TenDRA/feature/${api}.h)
JOPTS${api}+=	-f${PREFIX_TSPEC}/TenDRA/feature/${api}.h
. endif

. for startup in ${STARTUP_MACH}
.  if exists(${startup}/${api}.h)
JOPTS${api}+=	-f${startup}/${api}.h
.  endif
. endfor

APISRCS${api}!=	find ${PREFIX_TSPEC}/TenDRA/src/${api}.api -name '*.c'
APISRCS${api}:=	${APISRCS${api}:T}

. for src in ${APISRCS${api}}
${OBJ_SDIR}/apis/${api}.api/${src:R}.j: ${PREFIX_TSPEC}/TenDRA/src/${api}.api/${src}
	@${CONDCREATE} "${.TARGET:H}"
	@${ECHO} "==> Compiling ${api}.api/${src}"
	${TCC_IN_SITU} ${HACKS} ${TCCOPTS} ${CCOPTS} ${JOPTS} ${JOPTS${api}} \
		-I${PREFIX_TSPEC}/TenDRA/include/${api}.api \
		-o ${.TARGET} ${.ALLSRC} -Ymakelib -Xp

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
	${RMFILE} ${OBJ_SDIR}/apis/${api}.tl ${APIOBJS${api}}


install:: ${OBJ_SDIR}/apis/${api}.tl
	@${ECHO} "==> Installing ${api} API"
	@${CONDCREATE} "${PREFIX_API}"
	${INSTALL} -m 644 ${OBJ_SDIR}/apis/${api}.tl "${PREFIX_API}/${api}.tl"

.endfor


clean::


.endif	# !defined(_TENDRA_WORK_API_MK_)
