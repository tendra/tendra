# TenDRA make build infrastructure
#
# $Id$

.if !defined(_TENDRA_WORK_MACH_MK_)
_TENDRA_WORK_MACH_MK_=1

.include <tendra.base.mk>
.include <tendra.functions.mk>

.if !defined(MACHSUBDIR)
.BEGIN:
	@${ECHO} '$${MACHSUBDIR} must be set'
	@${EXIT} 1;
.endif



#
# Install machine subdirectory data.
#

# Relative to .CURDIR. XXX: ok?
IMACH=include
SMACH=startup

_REALINSTALL: .USE
	@${ECHO} "==> Installing ${MACHSUBDIR} machine directories"
	${CONDCREATE} "${MACH_BASE}/include" "${MACH_BASE}/startup"
	@cd ${MACHSUBDIR} && find ${IMACH} ${SMACH} -name '.*' -prune -o -print | \
	while read file; do \
		if ${TEST} -d $${file}; then \
			${ECHO} ${INSTALL} -m 755 ${MACH_BASE}/$${file}; \
			${INSTALL} -m 755 -d ${MACH_BASE}/$${file} || ${EXIT} $$?; \
		else \
			${ECHO} ${INSTALL} -m 644 $${file} ${MACH_BASE}/$${file}; \
			${INSTALL} -m 644 $${file} ${MACH_BASE}/$${file} || ${EXIT} $$?; \
		fi; \
	done



.endif	# !defined(_TENDRA_WORK_MACH_MK_)
