# $TenDRA$

PREFIX=		@PREFIX@
TMP_DIR=	@TMP_DIR@
MACH_OS=	@MACH_OS@
MACH_VERS=	@MACH_VERS@
MACH_CPU=	@MACH_CPU@
MACH_EXEC=	@MACH_EXEC@
MACH_DIR=	${PREFIX}/lib/TenDRA/machines
MACH_BASE=	${MACH_DIR}/${MACH_OS}/${MACH_VERS}/${MACH_CPU}
INSTALL_DIR=	${PREFIX}/lib/TenDRA
COMMON_DIR=	${INSTALL_DIR}/lib


BOOTSTRAP=	yes



# DON'T CHANGE ANYTHING BELOW THIS LINE

BUILD_OS=      @BUILD_OS@

.include "@SRC_DIR@/mk/config/config.@MACH_OS_LCASE@.mk" 
.include "@SRC_DIR@/mk/def/def.@MACH_OS_LCASE@.mk"

.if exists (@SRC_DIR@/mk/config/config.@MACH_OS_LCASE@.@MACH_CPU@.mk)
.include "@SRC_DIR@/mk/config/config.@MACH_OS_LCASE@.@MACH_CPU@.mk"
.endif
