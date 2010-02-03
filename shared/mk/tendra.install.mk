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
. include <tendra.api.mk>
.elif "${ENVFILE}" != ""
. include <tendra.env.mk>
.elif "${LIB}" != ""
. include <tendra.lib.mk>
.elif "${PROG}" != ""
. include <tendra.prog.mk>
.elif "${STARTUPSUBDIR}" != ""
. include <tendra.startup.mk>
.elif "${MACHSUBDIR}" != ""
. include <tendra.mach.mk>
.elif "${TDFLIB}" != ""
. include <tendra.tokdef.mk>
.else
#
# Nothing to install.
#
_REALINSTALL: .USE
.endif

# Install manual pages, if any. See also tendra.build.mk.
_MANINSTALL: .USE
.if "${MAN}" != ""
	@${ECHO} "==> Installing ${MAN} manual pages"
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
