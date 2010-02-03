# TenDRA make subdirectory traversal.
#
# $Id$

.if !defined(_TENDRA_SUBDIR_MK_)
_TENDRA_SUBDIR_MK_=1

.include <tendra.base.mk>
.include <tendra.functions.mk>

# TODO: make SUBDIR non-optional when this makefile is included explicitly
#.if !defined(SUBDIR)
#.BEGIN:
#	@${ECHO} '$${SUBDIR} must be set'
#	@${EXIT} 1;
#.endif



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
