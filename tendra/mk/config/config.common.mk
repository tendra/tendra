# $TenDRA$
#
# This holds the actual target for creating the config file.
# since this will always be common for all os's i moved it to it's own
# file.

config-create:
.if exists (${SRC_DIR}/config.mk)
	@echo CONFIG ALREADY EXISTS ${SRC_DIR}/config.mk
	@echo if you wish to reconfigure please use make re-config
	@echo
.else
	cat ${SRC_DIR}/mk/misc/default.config.mk |\
	sed \
	-e "s|@BUILD_OS@|${BUILD_OS}|g" \
	-e "s|@PREFIX@|${PREFIX}|g" \
	-e "s|@TMP_DIR@|${TMP_DIR}|g" \
	-e "s|@MACH_OS@|${MACH_OS}|g" \
	-e "s|@MACH_VERS@|${MACH_VERS}|g" \
	-e "s|@MACH_CPU@|${MACH_CPU}|g" \
	-e "s|@MACH_EXEC@|${MACH_EXEC}|g" \
	-e "s|@MACH_OS_LCASE@|${BUILD_OS}|g" \
	-e "s|@SRC_DIR@|${SRC_DIR}|g" \
	> ${SRC_DIR}/config.mk
	@echo "config file created! you can find it at: ${SRC_DIR}/config.mk"
.endif
