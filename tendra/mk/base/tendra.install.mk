# $TenDRA$

INSTALL_PREFIX=		${INSTALL_DIR}/${TENDRA_VER}/${MACH_OS}/${MACH_VERS}/${MACH_CPU}

.if defined(PROG)
INSTALL_TARGETS+=	install-bin
INSTALL_SUB+=		bin
.endif

.if defined(STARTUP)
INSTALL_TARGETS+=	install-startup
.endif

.if defined(API)
INSTALL_TARGETS+=	install-api
INSTALL_SUB+=		lib/include/${API}.api lib/include/shared/${API}.api
.endif

.if defined(INSTALL_ENV)
INSTALL_TARGETS+=	install-env
INSTALL_SUB+=		env
.endif

.if defined(PROG)
INSTALL_TARGETS+=	install-wrapper
.endif



# Our main target.
install-all: install-dir ${INSTALL_TARGETS}

# lib/startup: our startup files for compilation modes.
install-startup:
	${MKDIR} ${INSTALL_PREFIX}/startup/${STARTUP}
.for i in ${DATA}
	${INSTALL} ${INSTALL_FLAGS} ${.OBJDIR}/${i} \
		${INSTALL_PREFIX}/startup/${STARTUP}
.endfor

# lib/apis: our api files.
install-api:
	for i in ${.OBJDIR}.api/*.h; do \
		${INSTALL} $$i ${INSTALL_PREFIX}/lib/include/${API}.api; \
	done
	for i in ${.OBJDIR:C/apis/apis\/shared/}.api/*.h; do \
		${INSTALL} $$i ${INSTALL_PREFIX}/lib/include/shared/${API}.api; \
	done
	${INSTALL} ${.OBJDIR:C/apis/apis\/lib/}/${API}.tl \
		${INSTALL_PREFIX}/lib

# lib/env: our environment files.
install-env:
	cat ${SRC_DIR}/src/lib/env/common/default | \
	${SED} ${SED_INSTALL_OPTS} > ${INSTALL_PREFIX}/env/default
.for i in ${DATA_COMMON} ${DATA}
	${INSTALL} ${.OBJDIR}/${i} ${INSTALL_PREFIX}/env
.endfor

# installers/*, tools/*, utilities/*: our binary files.
install-bin:
	${INSTALL} ${INSTALL_FLAGS} ${.OBJDIR}/${PROG} ${INSTALL_PREFIX}/bin

install-dir:
	for i in ${INSTALL_SUB}; do \
		${MKDIR} ${INSTALL_PREFIX}/$$i; \
	done

#
# Hack; please fix
#
SED_WRAPPER_OPTS= -e "s%-INSTALL_PREFIX-%${INSTALL_PREFIX}%g"
install-wrapper:
	${CAT} ${SRC_DIR}/src/tools/tcc/tcc.sh | \
		${SED} ${SED_WRAPPER_OPTS} > ${PREFIX}/bin/tcc
	${CHMOD} +x ${PREFIX}/bin/tcc

.include "tendra.version.mk"
