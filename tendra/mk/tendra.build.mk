# TenDRA make build infrastructure
#
# $Id$

.include <tendra.base.mk>

# Build infrastructure framework

.if !target(.MAIN)
.MAIN: all
.endif

.SUFFIXES: .o .c .sid

.c.o:
	@${ECHO} Compiling ${.IMPSRC}...
	${CC} ${CCOPTS} -c ${.IMPSRC} -o ${OBJ_SDIR}/${.TARGET}

.sid.c:
	@${ECHO} Transforming ${.IMPSRC} and ${.IMPSRC:S/.sid/.act/}...
	${SID} ${SIDOPTS} ${.IMPSRC} ${.IMPSRC:S/.sid/.act/} ${.TARGET}\
		${.TARGET:S/.c/.h/}

all:
.if defined(API)
	@${MAKE} _OBJDIR
	@env MAKEOBJDIR=${OBJ_SDIR} ${MAKE} ${API}
.endif
.if defined(PROG)
	@${MAKE} _OBJDIR
	@env MAKEOBJDIR=${OBJ_SDIR} ${MAKE} ${PROG}
.endif

${API}:
	@${ECHO} Building ${API} API...
	${TSPEC} -v -w -I${BASE_DIR}/${APIS} -O${OBJ_DIR}/${APIS}/include\
		-S${OBJ_DIR}/${APIS}/building ${.TARGET}

${PROG}: ${OBJS}
	@${ECHO} Linking ${PROG}...
	${LD} ${LDOPTS} -o ${PROG} ${OBJS} ${LDCRT} ${LIBS}
.if defined(WRAPPER)
	@${ECHO} Adjusting paths for ${WRAPPER}...
	sed s'/@@MACH_BASE@@/${MACH_BASE:S/\//\\\//g}/g' ${BASE_DIR}/${TOOLS}/${PROG}/${WRAPPER} > ${OBJ_SDIR}/${WRAPPER}
.endif

clean:
.if defined(PROG)
	cd ${OBJ_SDIR}; \
		${REMOVE} ${PROG} ${PROG}.core core ${OBJS}
.endif
.if defined(CLEAN_EXTRA)
	${REMOVE} ${CLEAN_EXTRA}
.endif

install:
.if defined(API)
.if !exists(${INSTALL_DIR}/lib/building/${API}.api)
	${MKDIR} -p ${INSTALL_DIR}/lib/building/${API}.api
.endif
.if !exists(${INSTALL_DIR}/lib/include/${API}.api)
	${MKDIR} -p ${INSTALL_DIR}/lib/include/${API}.api
.endif
	cd ${OBJ_DIR}/${APIS}/building/${API}.api;\
	for file in M_${API} *.c; do\
		${INSTALL} -m 644 $$file ${INSTALL_DIR}/lib/building/${API}.api/$$file;\
	done
	cd ${OBJ_DIR}/${APIS}/include/${API}.api;\
	for file in *.h; do\
		${INSTALL} -m 644 $$file ${INSTALL_DIR}/lib/include/${API}.api/$$file;\
	done
.endif # API
.if defined(PROG)
	cd ${OBJ_SDIR};
.if !exists(PUBLIC_BIN)
	${MKDIR} -p ${PUBLIC_BIN}
.endif
.if defined(WRAPPER)
	${INSTALL} -m 755 ${OBJ_SDIR}/${PROG}.sh ${PUBLIC_BIN}/${PROG}
.endif
.if !exists(${MACH_BASE}/bin)
	${MKDIR} -p ${MACH_BASE}/bin
.endif
	${INSTALL} -m 755 ${OBJ_SDIR}/${PROG} ${MACH_BASE}/bin/${PROG}
.endif # PROG
# XXX: Very dirty hack...
.if defined(STARTUPSUBDIR)
.if !exists(${COMMON_DIR}/startup)
	${MKDIR} -p ${COMMON_DIR}/startup
.endif
.for entry in ${STARTUPSUBDIR}
	${MKDIR} -p ${COMMON_DIR}/startup/${entry}
	(cd ${entry} && for file in *;\
		do ${INSTALL} -m 644 $$file ${COMMON_DIR}/startup/${entry}/$$file;\
		done)
.endfor
.endif

_OBJDIR:
.if !exists(${OBJ_SDIR})
.if defined(API)
	@mkdir -p ${OBJ_DIR}/${APIS}
.else
	@mkdir -p ${OBJ_SDIR}
.endif
	@${ECHODIR} ${OBJ_SDIR} created for ${.CURDIR}
.endif

_SUBDIR: .USE
.if defined(SUBDIR) && !empty(SUBDIR)
.for entry in ${SUBDIR}
		@${ECHODIR} "Entering ${DIRPREFIX}${entry}"
		@${ECHODIR} "..Executing within ${entry}: ${MAKE} ${.TARGET}"
		@cd ${.CURDIR}/${entry}; \
			${MAKE} ${.TARGET} DIRPREFIX=${DIRPREFIX}${entry}/
.endfor
.endif

.for target in all clean install
${target}: _SUBDIR
.endfor
