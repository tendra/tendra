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
CAPIDIR=building/${API}.api
SAPIDIR=shared/${API}.api
HAPIDIR=${API}.api

# Absolute target dirs.
SINSTDIR=${INSTALL_DIR}/lib/include/${SAPIDIR}
HINSTDIR=${INSTALL_DIR}/lib/include/${HAPIDIR}
CINSTDIR=${INSTALL_DIR}/lib/${CAPIDIR}
LINSTDIR=${INSTALL_DIR}/lib

_REALINSTALL: .USE
	@${ECHO} "# Installing ${API} API"
	${CONDCREATE} "${HINSTDIR}" "${CINSTDIR}" "${LINSTDIR}";
	${INSTALL} -m 644 ${.OBJDIR}/${API}.tl ${LINSTDIR}
. for file in ${:!${ECHO} ${CAPIDIR}/*.c ${CAPIDIR}/M_${API}!:T}
	${INSTALL} -m 644 ${CAPIDIR}/${file} ${CINSTDIR}/${file}
. endfor
. for file in ${:!${ECHO} ${HAPIDIR}/*.h!:T}
	${INSTALL} -m 644 ${HAPIDIR}/${file} ${HINSTDIR}/${file}
. endfor
. if exists(${.OBJDIR}/${SAPIDIR})
	${CONDCREATE} "${SINSTDIR}" ;
.  for file in ${:!${ECHO} ${SAPIDIR}/*.h!:T}
	${INSTALL} -m 644 ${SAPIDIR}/${file} ${SINSTDIR}/${file}
.  endfor
. endif
.elif "${ENVFILE}" != ""
#
# Install environment(s).
#
_REALINSTALL: .USE
	@${ECHO} "# Installing ${ENVFILE} environments"
	${CONDCREATE} "${MACH_BASE}/env" ;
. for entry in ${ENVFILE}
	${INSTALL} -m 644 ${entry} ${MACH_BASE}/env/${entry}
. endfor
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
.  for file in ${:!${ECHO} ${envsub}/*!:T}
	${INSTALL} -m 644 ${envsub}/${file} ${MACH_BASE}/env/${file}
.  endfor
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
. for file in ${:!${ECHO} ${IMACH}/*!:T}
	${INSTALL} -m 644 ${IMACH}/${file} ${MACH_BASE}/include/${file}
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
	${INSTALL} -m 444 ${.CURDIR}/${man} ${MAN_DIR}/man${man:E}/${man}
. endfor
.endif

# Finally, glue all steps together.

# Make sure subdirs install after we're done.
.ORDER: _REALINSTALL _MANINSTALL _SUBDIR

# Depending on all not necessary but nice (verify it's not harmful!).
install: _REALINSTALL _MANINSTALL

.endif	# !defined(_TENDRA_INSTALL_MK_)
