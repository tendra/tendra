# TenDRA make install infrastructure
#
# $Id$

.if !defined(_TENDRA_INSTALL_MK_)
_TENDRA_INSTALL_MK_=1

.include <tendra.base.mk>
.include <tendra.functions.mk>

# Installation infrastructure framework. We come after tendra.build.mk.

# For {ENV, MACH, STARTUP}SUBDIR, a real Makefile should exist in each
# directory and control should be passed via standard SUBDIR mechanism.
# At the moment, we have to do all the work here, which is *ugly*.

# Real workers, mutually exclusive, follow.

.if "${API}" != ""
#
# Install API.
#

# Relative to .OBJDIR.
CAPIDIR=${.OBJDIR}/building
SAPIDIR=${.OBJDIR}/shared
HAPIDIR=${.OBJDIR}

# Absolute target dirs.
SINSTDIR=${INSTALL_DIR}/lib/include/shared
HINSTDIR=${INSTALL_DIR}/lib/include
CINSTDIR=${INSTALL_DIR}/lib/building
LINSTDIR=${INSTALL_DIR}/lib

_REALINSTALL: .USE
	@${ECHO} "# Installing ${API} API"
	${CONDCREATE} "${HINSTDIR}" "${CINSTDIR}" "${LINSTDIR}"
.if exists(${SAPIDIR}/${API}.api)
	${CONDCREATE} "${SINSTDIR}"
.endif
	${INSTALL} -m 644 ${.OBJDIR}/${API}.tl ${LINSTDIR}
	${TAR} -C ${CAPIDIR} -cf- ${API}.api | ${TAR} -C ${CINSTDIR} -xf-
	${TAR} -C ${HAPIDIR} -cf- ${API}.api | ${TAR} -C ${HINSTDIR} -xf-
.if exists(${SAPIDIR}/${API}.api)
	${TAR} -C ${SAPIDIR} -cf- ${API}.api | ${TAR} -C ${SINSTDIR} -xf-
. endif
.elif "${ENVFILE}" != ""
#
# Install environment(s).
#
_REALINSTALL: .USE
	@${ECHO} "# Installing ${ENVFILE} environments"
	${CONDCREATE} "${MACH_BASE}/env" ;
. for entry in ${ENVFILE}
	${INSTALL} -m 644 ${.OBJDIR}/${entry} ${MACH_BASE}/env/${entry}
. endfor
.elif "${LIB}" != ""
#
# Install a library.
#
_REALINSTALL: .USE
	@${ECHO} "# Installing lib${LIB}.a"
	${CONDCREATE} "${COMMON_DIR}/sys"
	${INSTALL} -m 755 lib${LIB}.a ${COMMON_DIR}/sys/lib${LIB}.a
.elif "${PROG}" != ""
#
# Install a program.
#
_REALINSTALL: .USE
	@${ECHO} "# Installing ${PROG}"
	${CONDCREATE} "${PUBLIC_BIN}" "${MACH_BASE}/bin"
	${INSTALL} -m 755 ${PROG} ${MACH_BASE}/bin/${PROG}
. if "${WRAPPER}" != ""
	${INSTALL} -m 755 ${WRAPPER} ${PUBLIC_BIN}/${PROG}
. endif
.elif "${ENVSUBDIR}" != ""
#
# Install startup environments. (XXX: seems it's not ever used in tree)
#
_REALINSTALL: .USE
	@${ECHO} "# Installing ${ENVSUBDIR} environment directories"
	${CONDCREATE} "${MACH_BASE}/env" \
		${ENVSUBDIR:S/^/${MACH_BASE}\/startup\//g}
. for envsub in ${ENVSUBDIR}
.  if exists(${envsub})
.   for file in ${:!${ECHO} ${envsub}/*!:T}
	if [ -f ${IMACH}/${file} ]; then \
		${INSTALL} -m 644 ${envsub}/${file} ${MACH_BASE}/env/${file}; \
	fi
.   endfor
.  endif
. endfor
.elif "${STARTUPSUBDIR}" != ""
#
# Install additional startup files (?).
#
_REALINSTALL: .USE
	@${ECHO} "# Installing ${STARTUPSUBDIR} startup directories"
	${CONDCREATE} ${STARTUPSUBDIR:S/^/${COMMON_DIR}\/startup\//g}
. for startsub in ${STARTUPSUBDIR}
.  for file in ${:!${ECHO} ${startsub}/*!:T}
	${INSTALL} -m 644 ${startsub}/${file} \
		${COMMON_DIR}/startup/${startsub}/${file}
.  endfor
. endfor
.elif "${MACHSUBDIR}" != ""
#
# Install machine subdirectory data.
#

# Relative to .CURDIR. XXX: ok?
IMACH=${MACHSUBDIR}/include
SMACH=${MACHSUBDIR}/startup

_REALINSTALL: .USE
	@${ECHO} "# Installing ${MACHSUBDIR} machine directories"
	${CONDCREATE} "${MACH_BASE}/include" "${MACH_BASE}/startup"
	# XXX: ${IMACH}/sys/* is not installed
. for file in ${:!${ECHO} ${IMACH}/*!:T}
	if [ -f ${IMACH}/${file} ]; then \
		${INSTALL} -m 644 ${IMACH}/${file} ${MACH_BASE}/include/${file}; \
	fi
. endfor
. for file in ${:!${ECHO} ${SMACH}/*!:T}
	${INSTALL} -m 644 ${SMACH}/${file} ${MACH_BASE}/startup/${file}
. endfor
.else
#
# Nothing to install.
#
_REALINSTALL: .USE
.endif

# Install manual pages, if any. See also tendra.build.mk.
_MANINSTALL: .USE
.if "${MAN}" != ""
	@${ECHO} "# Installing ${MAN} manual pages"
. for man in ${MAN}
	${CONDCREATE} "${MAN_DIR}/man${man:E}"
	${INSTALL} -m 644 ${.CURDIR}/${man} ${MAN_DIR}/man${man:E}/${man}
. endfor
.endif

# Finally, glue all steps together.

# Make sure subdirs install after we're done.
.ORDER: _REALINSTALL _MANINSTALL _SUBDIR

# Depending on all not necessary but nice (verify it's not harmful!).
install: _REALINSTALL _MANINSTALL

.endif	# !defined(_TENDRA_INSTALL_MK_)
