# $TenDRA$

INSTALL_PREFIX=		${INSTALL_DIR}/${TENDRA_VER}/${MACH_OS}/${MACH_VERS}/${MACH_CPU}

# If you do not see an INSTALL_SUB below for a specific target changes are it
# is set within the Makefile for that target.
.if defined(PROG)
INSTALL_TARGETS=	install-bin
INSTALL_SUB=		bin
.elif defined(INSTALL_STARTUP)
INSTALL_TARGETS=	install-startup
.elif defined(API)
INSTALL_TARGETS=	install-api
INSTALL_SUB=		lib/include
.elif defined(INSTALL_ENV)
INSTALL_TARGETS=	install-env
INSTALL_SUB=		env
.endif


# Our main target.
install-all: install-dir ${INSTALL_TARGETS}

# lib/startup: our startup files for compilation modes.
install-startup:
.for i in ${DATA}
	${INSTALL} ${INSTALL_FLAGS} ${.OBJDIR}/${i} ${INSTALL_PREFIX}/${INSTALL_SUB}
.endfor

# lib/apis: our api files.
install-api:
	@for i in ${.OBJDIR}.api/*.h; do \
		${INSTALL} $$i ${INSTALL_PREFIX}/${INSTALL_SUB}/${API}.api; \
	done

# lib/env: our environment files.
install-env:
.for i in ${DATA_COMMON} ${DATA}
	@${INSTALL} ${.OBJDIR}/${i} ${INSTALL_PREFIX}/${INSTALL_SUB}
.endfor

# installers/*, tools/*, utilities/*: our binary files.
install-bin:
	@${INSTALL} ${INSTALL_FLAGS} ${.OBJDIR}/${PROG} ${INSTALL_PREFIX}/${INSTALL_SUB}

install-dir:
	@${MKDIR} ${INSTALL_PREFIX}/${INSTALL_SUB}

.include "tendra.version.mk"
