# $TenDRA$

INSTALL_PREFIX=		${INSTALL_DIR}/${TENDRA_VER}/${MACH_OS}/${MACH_VERS}/${MACH_CPU}

.if defined(IMACHINE)
INSTALL_TARGETS+=	install-machine
INSTALL_SUB+=		lib/machines
.endif

.if defined(PROG)
INSTALL_TARGETS+=	install-bin
INSTALL_SUB+=		bin
.if !defined(NOMAN)
MAN+=			${PROG}.1
.endif
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
.endif

.if defined(MAN)
INSTALL_TARGETS+=	install-man
.endif

.if defined(PROG)
INSTALL_TARGETS+=	install-wrapper
.endif

.if defined(SHLIB)
INSTALL_TARGETS+=	install-shlib
INSTALL_SUB+=		lib/sys
.endif



# Our main target.
install-all: install-dir ${INSTALL_TARGETS}

# lib/machines: our machine dependent files.
install-machine:
.for i in ${MAKEDIR}
	${MKDIR} -p ${INSTALL_PREFIX}/lib/machines/${i}
.endfor
.for i in ${DATA_INCLUDE}
	${INSTALL} ${.OBJDIR}/${i} \
		${INSTALL_PREFIX}/lib/machines/${i:C/(.*)\/.*$/\1/}
.endfor
.for i in ${DATA_STARTUP}
	${INSTALL} ${.OBJDIR}/${i} ${INSTALL_PREFIX}/lib/machines/startup
.endfor

# lib/startup: our startup files for compilation modes.
install-startup:
	${MKDIR} -p ${INSTALL_PREFIX}/lib/startup/${STARTUP}
.for i in ${DATA}
	${INSTALL} ${INSTALL_FLAGS} ${.OBJDIR}/${i} \
		${INSTALL_PREFIX}/lib/startup/${STARTUP}
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
	${MKDIR} -p ${INSTALL_PREFIX}/env
	${SED} ${SED_INSTALL_OPTS} ${SRC_DIR}/src/lib/env/common/default > \
		${INSTALL_PREFIX}/env/default
.for i in ${DATA_COMMON} ${DATA}
	${INSTALL} ${.OBJDIR}/${i} ${INSTALL_PREFIX}/env
.endfor

# installers/*, tools/*, utilities/*: our binary files.
install-bin:
	${INSTALL} ${INSTALL_FLAGS} ${.OBJDIR}/${PROG} ${INSTALL_PREFIX}/bin

# installers/*, producers/*, tools/*, utilities/*: our man pages.
install-man:
.for i in ${MAN}
	${MKDIR} -p ${PREFIX}/man/man${i:E}
	${INSTALL} ${.CURDIR}/${i} ${PREFIX}/man/man${i:E}
.endfor

# lib/sys: our shared libraries
install-shlib:
	${INSTALL} ${.OBJDIR}/${SHLIB} ${INSTALL_PREFIX}/lib/sys

install-dir:
	for i in ${INSTALL_SUB}; do \
		${MKDIR} ${INSTALL_PREFIX}/$$i; \
	done

#
# Hack; please fix
#
SED_WRAPPER_OPTS= -e "s%-INSTALL_PREFIX-%${INSTALL_PREFIX}%g"
install-wrapper:
	${MKDIR} -p ${PREFIX}/bin
	${SED} ${SED_WRAPPER_OPTS} ${SRC_DIR}/src/tools/tcc/tcc.sh > \
		${PREFIX}/bin/tcc
	${CHMOD} +x ${PREFIX}/bin/tcc

.include "tendra.version.mk"
