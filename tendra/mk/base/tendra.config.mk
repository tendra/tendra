# $TenDRA$
#
# This will check to see if config.mk exists in the parent TenDRA directory.
# If it doesn't it will spit out a notice to ask the user to supply make <os>.
# For now there is no sanity checking on the results to make sure that
# everything is ok, it's just assumed (we can add this later).
#

# XXX: sometimes this file is included twice
.if !defined(HAVE_CONFIG_MK)
HAVE_CONFIG_MK=1

BUILD_TARGETS=	aix cygwin32 darwin freebsd hpux irix linux netbsd \
		openbsd osf1 qnx solaris sunos tru64

config-check:
.if exists (${SRC_DIR}/config.mk)
HAVE_CONF=	yes
.include "${SRC_DIR}/config.mk"
.else
	@echo "YOU HAVE NOT CONFIGURED TenDRA YET"
	@echo ""
	@echo "Available targets are:"
	@echo "  ${BUILD_TARGETS}"
	@echo ""
	@echo "In order to configure TenDRA, please execute make with the"
	@echo "proper target to create config.mk"
	@echo ""
.endif


${BUILD_TARGETS}: config-create

.endif


.for ARCH in ${BUILD_TARGETS}
.if make(${ARCH})
BUILD_OS=	${ARCH}

# Handle special case architechtures
.if ${BUILD_OS} == tru64
BUILD_OS=	osf1
.endif

.include "../def/def.${BUILD_OS}.mk"
.include "../config/config.${BUILD_OS}.mk"
.endif
.endfor

