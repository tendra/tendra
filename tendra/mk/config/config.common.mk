# $TenDRA$
#
# This holds the actual target for creating the config file.
# Since this will always be common for all OS's I moved it to it's own
# file.

# XXX: sometimes this file is included twice
.if !defined(HAVE_COMMON_MK)
HAVE_COMMON_MK=1

config-create:
.if exists (${SRC_DIR}/config.mk)
	@echo CONFIG ALREADY EXISTS: ${SRC_DIR}/config.mk
	@echo If you wish to reconfigure please use make re-config
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
	-e "s|@SRC_ENV@|${SRC_ENV}|g" \
	-e "s|@OBJ_PREFIX@|${SRC_DIR}/obj|g" \
	-e "s|@OBJ_ENV@|lib/env/${ENV_SRC}|g" \
	-e "s|@MAN_COMPRESS@|${MAN_COMPRESS}|g" \
	> ${SRC_DIR}/config.mk
	@echo "Config file created! You can find it at: ${SRC_DIR}/config.mk"
.endif

.endif
