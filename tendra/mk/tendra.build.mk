# TenDRA make build infrastructure
#
# $Id$

.include <tendra.base.mk>

# Build infrastructure framework

.if !target(.MAIN)
.MAIN: all
.endif

.SUFFIXES: .o .c .sid .j .pl

.c.o:
	@${ECHO} Compiling ${.IMPSRC}...
	${CC} ${CCOPTS} -c ${.IMPSRC} -o ${OBJ_SDIR}/${.TARGET}

.pl.j:
	@${ECHO} Transforming ${.IMPSRC}
	${TPL} ${.IMPSRC} ${OBJ_SDIR}/${.TARGET}

.sid.c:
	@${ECHO} Transforming ${.IMPSRC} and ${.IMPSRC:S/.sid/.act/}...
	${SID} ${SIDOPTS} ${.IMPSRC} ${.IMPSRC:S/.sid/.act/} ${.TARGET}\
		${.TARGET:S/.c/.h/}

.if defined(PROG)
.if !defined(MAN)
.if exists(${PROG}.1)
MAN=    ${PROG}.1
.endif	# exists(${PROG}.1)
.endif  # !defined(MAN)
.endif

all:
.if defined(API)
	@${MAKE} _OBJDIR
	@env MAKEOBJDIR=${OBJ_SDIR} ${MAKE} ${API}
.endif
.if defined(ENVFILE)
	@${MAKE} _OBJDIR
.for entry in ${ENVFILE}
	@${ECHO} Fixing paths for environment ${entry}...
	sed -e 1,\$$s%-MACH-%${OSFAM}/${BLDARCH}%g\
		-e 1,\$$s%-MACHDIR-%${MACH_BASE}%g\
		-e 1,\$$s%-BINDIR-%${MACH_BASE}/bin%g\
		-e 1,\$$s%-ENVDIR-%${MACH_BASE}/env%g\
		-e 1,\$$s%-LIBDIR-%${MACH_BASE}/lib%g\
		-e 1,\$$s%-INCLDIR-%${COMMON_DIR}/include%g\
		-e 1,\$$s%-STARTUPDIR-%${COMMON_DIR}/startup%g\
		-e 1,\$$s%-TMPDIR-%${TMP_DIR}%g ${entry} >\
		${OBJ_SDIR}/${entry}
.endfor
.if defined(ENVEXTRA)
	cat ${ENVEXTRA} >> ${OBJ_SDIR}/../../../common/default
.endif
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
	sed -e 1,\$$s%@@MACH_BASE@@%${MACH_BASE}%g ${BASE_DIR}/${TOOLS}/${PROG}/${WRAPPER} > ${OBJ_SDIR}/${WRAPPER}
.endif

clean: .PHONY
.if defined(PROG)
	cd ${OBJ_SDIR}; \
		${REMOVE} ${PROG} ${PROG}.core core ${OBJS}
.endif
.if defined(CLEAN_EXTRA)
	${REMOVE} ${CLEAN_EXTRA}
.endif

cleandir: .PHONY
	${REMOVE} -r ${OBJ_SDIR}

_OBJDIR:
.if !exists(${OBJ_SDIR})
.if defined(API)
	@${MKDIR} -p ${OBJ_DIR}/${APIS}
.else
	@${MKDIR} -p ${OBJ_SDIR}
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
