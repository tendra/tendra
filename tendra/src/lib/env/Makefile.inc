# $TenDRA$

#SED_OPTS= \
#-e s%-MACH-%${MACH_OS}/${MACH_CPU}%g \
#-e s%-MACHDIR-%${MACH_BASE}%g \
#-e s%-BINDIR-%${MACH_BASE}/bin%g \
#-e s%-ENVDIR-%${MACH_BASE}/env%g \
#-e s%-LIBDIR-%${MACH_BASE}/lib%g \
#-e s%-INCLDIR-%${COMMON_DIR}/include%g \
#-e s%-STARTUPDIR-%${COMMON_DIR}/startup%g \
#-e s%-TMPDIR-%${TEMP_DIR}%g

# this is a temp hack so the api libraries can be built.
# eventually something better will be sorted out, the whole
# env dir needs to be sorted out.
TPREFIX= ${SRC_DIR}/obj
TMACH_DIR = ${TPREFIX}/lib/TenDRA/machines
TMACH_BASE= ${MACH_DIR}/${MACH_OS}/${MACH_VERS}/${MACH_CPU}
TINSTALL_DIR= ${TPREFIX}/lib/
TCOMMON_DIR= ${TINSTALL_DIR}
TTMP_DIR= /tmp


SED_OPTS= \
-e s%-MACH-%${TMACH_OS}/${MACH_CPU}%g \
-e s%-MACHDIR-%${TMACH_BASE}%g \
-e s%-BINDIR-%${TMACH_BASE}/bin%g \
-e s%-ENVDIR-%${TMACH_BASE}/env%g \
-e s%-LIBDIR-%${TMACH_BASE}/lib%g \
-e s%-INCLDIR-%${TCOMMON_DIR}/include%g \
-e s%-STARTUPDIR-%${TCOMMON_DIR}/startup%g \
-e s%-TMPDIR-%/tmp%g \
-e s%-OBJDIR-%${SRC_DIR}/obj%g \

# common directory
DATA_COMMON=	16bit 32bit Goption K-PIC K-ieee K-noieee K-prom \
	Versions Xa Xc Xp Xs Xt Xw aes alloca ansi bsd_extn \
	building c c++ common compact cose default default.extra \
	gcc iso longlong makelib motif_1_1 motif_1_2 motif_private \
	mse pl_tdf posix posix1 posix2 status strict_mot_1_2 \
	strict_posix strict_svid3 strict_xpg3 svid3 system \
	system+ target_tok tcc_diag tcc_pp tcc_prof tcc_time tdf_ext \
	tdp tnc tsimp unix95 wsl x5_aw x5_ext x5_lib x5_mit x5_mu \
	x5_private x5_proto x5_t xpg3 xpg4 default-build

DEPEND_SRC=	${DATA} ${DATA_COMMON}

${DATA_COMMON}:
	@echo "${SRC_DIR}/src/lib/env/common/${.TARGET} -> ${.OBJDIR}/${.TARGET}"
	@cat ${SRC_DIR}/src/lib/env/common/${.TARGET} | \
	  ${SED} ${SED_OPTS} > ${.OBJDIR}/${.TARGET}
${DATA}:
	@echo "${.CURDIR}/${.TARGET} -> ${.OBJDIR}/${.TARGET}"
	@cat ${.CURDIR}/${.TARGET} | \
	  ${SED} ${SED_OPTS} > ${.OBJDIR}/${.TARGET}

CLEANFILES=	${DATA} ${DATA_COMMON}
