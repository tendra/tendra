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



install-all: install-dir ${INSTALL_TARGETS}


install-dir:
	@echo mkdir -p ${INSTALL_PREFIX}/${INSTALL_SUB}

install-env:
.for i in "${DATA_COMMON} ${DATA}"
	@echo install ${.OBJDIR}/${i} ${INSTALL_PREFIX}/${INSTALL_SUB}
.endfor


install-bin:
	@echo ${INSTALL} ${INSTALL_FLAGS} ${.OBJDIR}/${PROG} ${INSTALL_PREFIX}/${INSTALL_SUB}

.include "tendra.version.mk"
