# $TenDRA$

# default env file
DATA_DEFAULT=	default
# default-build is used for *building* only, don't install it
DATA_DEFAULT_BUILD=	default-build

# common directory
DATA_COMMON=	16bit 32bit Goption K-PIC K-ieee K-noieee K-prom \
	Versions Xa Xc Xp Xs Xt Xw alloca ansi bsd_extn \
	building c c++ c99 common compact cose \
	gcc iso longlong makelib motif_1_1 motif_1_2 motif_private \
	mse pl_tdf posix posix1 posix2 status strict_mot_1_2 \
	strict_posix strict_svid3 strict_xpg3 svid3 system \
	system+ target_tok tcc_diag tcc_pp tcc_prof tcc_time tdf_ext \
	tdp tnc tsimp unix95 wsl x5_aw x5_ext x5_lib x5_mit x5_mu \
	x5_private x5_proto x5_t xpg3 xpg4

DEPEND_SRC=	${DATA} ${DATA_COMMON} ${DATA_DEFAULT} ${DATA_DEFAULT_BUILD}

INSTALL_TARGETS=	install-env

${DATA}:
	@${BIN_CP} ${ARGS_CP} -R ${.CURDIR}/${.TARGET} ${.OBJDIR}/${.TARGET}

${DATA_COMMON}:
	@${BIN_CP} ${ARGS_CP} -R ${SRC_DIR}/src/lib/env/common/${.TARGET} ${.OBJDIR}/${.TARGET}


${DATA_DEFAULT} ${DATA_DEFAULT_BUILD}:
	cat ${SRC_DIR}/src/lib/env/common/${.TARGET} \
		${.CURDIR}/default.extra | \
		${BIN_SED} ${SED_DEFAULT} | \
		${BIN_SED} ${SED_DEFAULT_BIN} | \
		${BIN_SED} ${SED_DEFAULT_LIB} > \
		${.OBJDIR}/${.TARGET}


CLEANFILES=	${DATA} ${DATA_COMMON} ${DATA_DEFAULT}

SED_DEFAULT=	\
		-e "s%@MACH_CPU@%${MACH_CPU}%" \
		-e "s%@BUILD_OS@%${BUILD_OS}%" \
		-e "s%@BUILD_ENV@%${SRC_ENV}%"

# Binaries
SED_DEFAULT_BIN= \
		-e "s|-BIN_AS-|${BIN_AS}|g" \
		-e "s|-BIN_AS1-|${BIN_AS1}|g" \
		-e "s|-BIN_CC-|${BIN_CC}|g" \
		-e "s|-BIN_GAS-|${BIN_GAS}|g" \
		-e "s|-BIN_LD-|${BIN_LD}|g" \
		-e "s|-BIN_TIME-|${BIN_TIME}|g" \
		-e "s|-BIN_AS11_31-|${BIN_AS11_31}|g"

# Libraries
SED_DEFAULT_LIB= \
		-e "s|-LIB_AOUT_CRT0-|${LIB_AOUT_CRT0}|g" \
		-e "s|-LIB_LIBG_EXP-|${LIB_LIBG_EXP}|g" \
		-e "s|-LIB_CRT0-|${LIB_CRT0}|g" \
		-e "s|-LIB_CRT1-|${LIB_CRT1}|g" \
		-e "s|-LIB_CRTBEGIN-|${LIB_CRTBEGIN}|g" \
		-e "s|-LIB_CRTEND-|${LIB_CRTEND}|g" \
		-e "s|-LIB_CRTI-|${LIB_CRTI}|g" \
		-e "s|-LIB_CRTN-|${LIB_CRTN}|g" \
		-e "s|-LIB_FCRT1-|${LIB_FCRT1}|g" \
		-e "s|-LIB_GCRT0-|${LIB_GCRT0}|g" \
		-e "s|-LIB_GCRT1-|${LIB_GCRT1}|g" \
		-e "s|-LIB_LD_LINUX_1-|${LIB_LD_LINUX_1}|g" \
		-e "s|-LIB_LD_LINUX_2-|${LIB_LD_LINUX_2}|g" \
		-e "s|-LIB_MCRT0-|${LIB_MCRT0}|g" \
		-e "s|-LIB_MCRT1-|${LIB_MCRT1}|g" \
		-e "s|-LIB_PCRT0-|${LIB_PCRT0}|g" \
		-e "s|-LIB_VALUES_XA-|${LIB_VALUES_XA}|g" \
		-e "s|-LIB_VALUES_XC-|${LIB_VALUES_XC}|g" \
		-e "s|-LIB_VALUES_XT-|${LIB_VALUES_XT}|g"
