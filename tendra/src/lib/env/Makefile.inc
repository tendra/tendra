# $TenDRA$

SED_OPTS= -e "s%@MACH_CPU@%${MACH_CPU}%" -e "s%@BUILD_OS@%${BUILD_OS}%"

# default env file for *BUILDING* purposes only this is NOT installed.
DATA_DEFAULT=	default-build default

# common directory
DATA_COMMON=	16bit 32bit Goption K-PIC K-ieee K-noieee K-prom \
	Versions Xa Xc Xp Xs Xt Xw aes alloca ansi bsd_extn \
	building c c++ common compact cose \
	gcc iso longlong makelib motif_1_1 motif_1_2 motif_private \
	mse pl_tdf posix posix1 posix2 status strict_mot_1_2 \
	strict_posix strict_svid3 strict_xpg3 svid3 system \
	system+ target_tok tcc_diag tcc_pp tcc_prof tcc_time tdf_ext \
	tdp tnc tsimp unix95 wsl x5_aw x5_ext x5_lib x5_mit x5_mu \
	x5_private x5_proto x5_t xpg3 xpg4

DEPEND_SRC=	${DATA} ${DATA_COMMON} ${DATA_DEFAULT}

INSTALL_TARGETS=	install-env

${DATA}:
	@${CP} ${CP_ARGS} -R ${.CURDIR}/${.TARGET} ${.OBJDIR}/${.TARGET}

${DATA_COMMON}:
	@${CP} ${CP_ARGS} -R ${SRC_DIR}/src/lib/env/common/${.TARGET} ${.OBJDIR}/${.TARGET}


${DATA_DEFAULT}:
	cat ${SRC_DIR}/src/lib/env/common/${.TARGET} | \
		${SED} ${SED_OPTS} > ${.OBJDIR}/${.TARGET}

CLEANFILES=	${DATA} ${DATA_COMMON} ${DATA_DEFAULT}

SED_INSTALL_OPTS= -e "s%-BINDIR-%<TENDRA_BINDIR>%g" \
                  -e "s%-LIBDIR-%<TENDRA_LIBDIR>%g" \
                  -e "s%-STARTUPDIR-%<TENDRA_STARTUPDIR>%g" \
                  -e "s%-INCLDIR-%<TENDRA_INCLDIR>%g" \
                  -e "s%-TMPDIR-%<TENDRA_TMPDIR>%g" \
                  -e "s%-ENVDIR-%<TENDRA_ENVDIR>%g" \
                  -e "s%-AS-%${AS}%g" \
                  -e "s%-LD-%${LD}%g" \
		  -e "s%-CRT0-%${CRT0}%g" \
		  -e "s%-CRT1-%${CRT1}%g" \
		  -e "s%-CRTN-%${CRTN}%g" 
