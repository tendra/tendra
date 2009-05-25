# TenDRA make subdirectory traversal.
#
# This is shared for both bootstrap and the build proper.
#
# $Id$

.if !defined(_TENDRA_SUBDIR_MK_)
_TENDRA_SUBDIR_MK_=1

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

.endif	# !defined(_TENDRA_SUBDIR_MK_)
