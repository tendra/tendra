# $TenDRA$
#
# this will check to see if config.inc exists in the parent TenDRA directory.
# if it dosn't it will spit out a notice to ask the user to supply make <os>
# for now there is no sanity checking on the results to make sure that everything
# is ok, it's just assumed (we can add this later)
#

BUILD_TARGETS=	freebsd

reconfig:
.if exists (${SRC_DIR}/config.mk)
	cp ${SRC_DIR}/config.mk ${SRC_DIR}/backup.config.mk
	rm ${SRC_DIR}/config.mk
	${MAKE} ${BUILD_OS}
.endif

config-check:
.if exists (${SRC_DIR}/config.mk)
HAVE_CONF=	yes
.include "${SRC_DIR}/config.mk"
.else
	@echo "YOU HAVE NOT CONFIGURED TenDRA YET"
	@echo ""
	@echo "available targets are:"
	@echo "  freebsd"
	@echo ""
	@echo "In order to configure TenDRA please execute make with the"
	@echo "proper targets to create config.mk"
	@echo ""
.endif


${BUILD_TARGETS}: config-create

.if make(freebsd)
BUILD_OS=	freebsd
.include "../config/config.freebsd.mk"
.endif
