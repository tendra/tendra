# $TenDRA$
#
# This holds the actual target for creating the config file.
# Since this will always be common for all OS's I moved it to it's own
# file.
#
# Binaries needed to build TenDRA is tested for existance and being executable.
# Any new binary dependencies added to the buildprocess should be addded to the
# below tests.

# XXX: sometimes this file is included twice
.if !defined(HAVE_COMMON_MK)
HAVE_COMMON_MK=1


SED_OPT_VAR=	\
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
	-e "s|@SRC_MACHINES@|${SRC_MACHINES}|g" \
	-e "s|@OBJ_PREFIX@|${SRC_DIR}/obj|g" \
	-e "s|@MAN_COMPRESS@|${MAN_COMPRESS}|g" \
	-e "s|@MAN_INSTALL@|${MAN_INSTALL}|g" \
	-e "s|@PREFIX@|${PREFIX}|g"


.if defined(NO_RANLIB)
SED_OPT_COND=	-s "^\#NO_RANLIB|NO_RANLIB|"
.endif


config-create:
.if exists (${SRC_DIR}/config.mk)
	@echo "CONFIG ALREADY EXISTS: ${SRC_DIR}/config.mk"
	@echo "* You must manually delete config.mk and re-execute"
	@echo "  make <OS>."
	@echo "* Type make after deleting config.mk for a list of"
	@echo "  available targets."
	@echo
.else
	@echo "===> Verifying required binaries"
	@echo "Adjust to correct path in ${SRC_DIR}/mk/def/def.${.TARGETS}.mk if any test fails."
	@echo ${BIN_AR}
	@${BIN_TEST} -x "${BIN_AR}"
	@echo ${BIN_AWK}
	@${BIN_TEST} -x "${BIN_AWK}"
	@echo ${BIN_CAT}
	@${BIN_TEST} -x "${BIN_CAT}"
	@echo ${BIN_CC}
	@${BIN_TEST} -x "${BIN_CC}"
	@echo ${BIN_CHMOD}
	@${BIN_TEST} -x "${BIN_CHMOD}"
	@echo ${BIN_CP}
	@${BIN_TEST} -x "${BIN_CP}"
	@echo ${BIN_ECHO}
	@${BIN_TEST} -x "${BIN_ECHO}"
	@echo ${BIN_GREP}
	@${BIN_TEST} -x "${BIN_GREP}"
	@echo ${BIN_GZIP}
	@${BIN_TEST} -x "${BIN_GZIP}"
	@echo ${BIN_MKDIR}
	@${BIN_TEST} -x "${BIN_MKDIR}"
.if !defined(NO_RANLIB)
	@echo ${BIN_RANLIB}
	@${BIN_TEST} -x "${BIN_RANLIB}"
.endif
	@echo ${BIN_RM}
	@${BIN_TEST} -x "${BIN_RM}"
	@echo ${BIN_SED}
	@${BIN_TEST} -x "${BIN_SED}"
	@echo ${BIN_SH}
	@${BIN_TEST} -x "${BIN_SH}"
	@echo ${BIN_UNAME}
	@${BIN_TEST} -x "${BIN_UNAME}"
	@echo "===> Writing configuration"
	@cat ${SRC_DIR}/mk/misc/default.config.mk \
	|sed ${SED_OPT_VAR} \
	> ${SRC_DIR}/config.mk
	@echo "Config file created! You can find it at: ${SRC_DIR}/config.mk"
.endif

.endif
