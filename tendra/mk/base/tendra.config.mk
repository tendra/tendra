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

BUILD_TARGETS=	cygwin32 darwin freebsd linux netbsd openbsd osf1 tru64

config-check:
.if exists (${SRC_DIR}/config.mk)
HAVE_CONF=	yes
.include "${SRC_DIR}/config.mk"
.else
	@echo "YOU HAVE NOT CONFIGURED TenDRA YET"
	@echo ""
	@echo "available targets are:"
	@echo "  ${BUILD_TARGETS}"
	@echo ""
	@echo "In order to configure TenDRA please execute make with the"
	@echo "proper targets to create config.mk"
	@echo ""
.endif


${BUILD_TARGETS}: config-create

.endif

.if make(cygwin32)
BUILD_OS=	cygwin32
.include "../config/config.cygwin32.mk"
.endif

.if make(darwin)
BUILD_OS=	darwin
.include "../config/config.darwin.mk"
.endif

.if make(freebsd)
BUILD_OS=	freebsd
.include "../config/config.freebsd.mk"
.endif

.if make(linux)
BUILD_OS=	linux
.include "../config/config.linux.mk"
.endif

.if make(netbsd)
BUILD_OS=	netbsd
.include "../config/config.netbsd.mk"
.endif

.if make(openbsd)
BUILD_OS=	openbsd
.include "../config/config.openbsd.mk"
.endif

.if make(osf1) || make(tru64)
BUILD_OS=	osf1
.include "../config/config.osf1.mk"
.endif
