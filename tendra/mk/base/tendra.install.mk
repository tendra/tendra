# $TenDRA$

INSTALL_PREFIX=		${INSTALL_DIR}/${TENDRA_VER}/${MACH_OS}/${MACH_VERS}/${MACH_CPU}

.if defined(PROG)
INSTALL_TARGETS=	install-bin
INSTALL_SUB=		bin
.endif

# this is broken.
INSTALL_TARGETS=	
.if (${INSTALL_TARGETS} == "install-env")
INSTALL_SUB=		env
.endif


# Our main target.
install-all: install-dir ${INSTALL_TARGETS}


install-dir:
	@echo mkdir -p ${INSTALL_PREFIX}/${INSTALL_SUB}

# lib/env: our environment files.
install-env:
.for i in "${DATA_COMMON} ${DATA}"
	@echo install ${.OBJDIR}/${i} ${INSTALL_PREFIX}/${INSTALL_SUB}
.endfor

# installers/*, tools/*, utilities/*: our binary files.
install-bin:
	@echo ${INSTALL} ${INSTALL_FLAGS} ${.OBJDIR}/${PROG} ${INSTALL_PREFIX}/${INSTALL_SUB}

.include "tendra.version.mk"
