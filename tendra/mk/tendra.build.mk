# TenDRA make build infrastructure
#
# $Id$

.include <tendra.base.mk>

# Do some pretty-printing.
PARTIMP=	${.IMPSRC:C/^${BASE_DIR}\///1}
WRKDIR=		${.CURDIR:C/^${BASE_DIR}\///1}

# The main target is synthetised based upon actual needs.
.if !target(.MAIN)
.MAIN: all
.endif

# Implied rules.

.SUFFIXES: .o .c .sid .j .pl

.c.o:
	@${ECHO} "# Compiling ${PARTIMP}"
	${CC} ${CCOPTS} -c ${.IMPSRC} -o ${.TARGET}

.pl.j:
	@${ECHO} "# Transforming ${PARTIMP}"
	${TPL} ${.IMPSRC} ${.TARGET}

.sid.c:
	@${ECHO} "# Transforming ${PARTIMP} and ${PARTIMP:S/.sid/.act/}"
	${SID} ${SIDOPTS} ${.IMPSRC} ${.IMPSRC:S/.sid/.act/} ${.TARGET} \
		${.TARGET:S/.c/.h/}

# Do it all. Real workers, mutually exclusive, follow.

.if "${API}" != ""
#
# Build API.
#
_REALWORK: .USE
	@${ECHO} "# Building ${API} API"
	${TSPEC} -I${BASE_DIR}/${APIS} -O./ -S./building ${API}

_objdir= 	${OBJ_DIR}/${APIS}
.elif "${ENVFILE}" != ""
#
# Build environments.
#
fixenv.sed:
	@${ECHO} "# Create ${.TARGET}"
	@${ECHO} "1,\$$s%-MACH-%${OSFAM}/${BLDARCH}%g" 		> ${.TARGET}
	@${ECHO} "1,\$$s%-MACHDIR-%${MACH_BASE}%g" 		>> ${.TARGET}
	@${ECHO} "1,\$$s%-BINDIR-%${MACH_BASE}/bin%g" 		>> ${.TARGET}
	@${ECHO} "1,\$$s%-ENVDIR-%${MACH_BASE}/env%g" 		>> ${.TARGET}
	@${ECHO} "1,\$$s%-LIBDIR-%${MACH_BASE}/lib%g" 		>> ${.TARGET}
	@${ECHO} "1,\$$s%-INCLDIR-%${COMMON_DIR}/include%g" 	>> ${.TARGET}
	@${ECHO} "1,\$$s%-STARTUPDIR-%${COMMON_DIR}/startup%g" 	>> ${.TARGET}
	@${ECHO} "1,\$$s%-TMPDIR-%${TMP_DIR}%g" 		>> ${.TARGET}

_REALWORK: fixenv.sed .USE
	@${ECHO} "# Fixing paths for ${ENVFILE} environments"
. for entry in ${ENVFILE}
	sed -f fixenv.sed ${.CURDIR}/${entry} > ${entry}
. endfor
. if "${ENVEXTRA}" != ""
	cat ${.CURDIR}/${ENVEXTRA} >> ${OBJ_SDIR}/../../../common/default
. endif

_objdir=	${OBJ_SDIR}
.elif "${PROG}" != ""
#
# Build a program.
#
. if !defined(MAN) && exists(${.CURDIR}/${PROG}.1)
MAN=    	${PROG}.1
. endif

_REALWORK: ${OBJS} .USE
	@${ECHO} "# Linking ${WRKDIR}/${PROG}"
	${LD} ${LDOPTS} -o ${PROG} ${OBJS} ${LDCRT} ${LIBS}
. if defined(WRAPPER)
	@${ECHO} "# Adjusting paths for ${WRAPPER}"
	sed -e 1,\$$s%@@MACH_BASE@@%${MACH_BASE}%g \
		-e 1,\$$s%@@PREFIX@@%${PREFIX}%g \
		${.CURDIR}/${WRAPPER} > ${WRAPPER}
. endif

CLEAN_EXTRA+=	${PROG} ${PROG}.core core ${OBJS}
_objdir=	${OBJ_SDIR}
.else
#
# Nothing to do here.
#
_REALWORK:
.endif

# Suppport targets.

# Remove registered garbage.
clean:
.if "${CLEAN_EXTRA}" != ""
	@${ECHO} "# Cleaning ${.CURDIR}"
	${REMOVE} ${CLEAN_EXTRA}
.endif

# Clean objdir blindly.
cleandir:
.if "${_objdir}" != ""
	${REMOVE} ${_objdir}/* 2> /dev/null
.endif

# Remove obj symlink from curdir.
cleanobj:
.if "${_objdir}" != ""
	@if ${TEST} -h ${.CURDIR}/obj ; then \
		${ECHO} "# Removing obj link ${WRKDIR}/obj" ; \
		${REMOVE} ${.CURDIR}/obj ; \
		${REMOVE} ${OBJ_DIR_INDICATOR} 2> /dev/null ; \
	fi
.endif

# Create objdir and its symlink.
obj:
.if "${_objdir}" != "" && (!exists(${_objdir}) || !exists(obj))
	@${ECHO} "# Creating objdir ${_objdir}"
	@${MKDIR} -p ${_objdir}
	@${LN} -sf ${_objdir} ${.CURDIR}/obj
.endif

# Glue all the steps together.

all: _REALWORK

# Make sure subdirs are walked after real work is done.
.ORDER: _REALWORK _SUBDIR

# Proceed to subdirs.
_SUBDIR: .USE
.if defined(SUBDIR) && !empty(SUBDIR)
. for entry in ${SUBDIR}
	@cd ${.CURDIR}/${entry}; ${MAKE} ${.TARGET}
. endfor
.endif

# Ensure existence of basic targets.
.for target in obj all clean install cleanobj cleandir
${target}: _SUBDIR .PHONY
.endfor
