# TenDRA make subdirectory traversal.
#
# $Id$

.if !defined(_TENDRA_SUBDIR_MK_)
_TENDRA_SUBDIR_MK_=1

.include <tendra.base.mk>
.include <tendra.functions.mk>

.if !defined(SUBDIR)
.BEGIN:
	@${ECHO} '$${SUBDIR} must be set'
	@${EXIT} 1;
.endif

.if ${SUBDIR:Munknown}
.BEGIN:
	@${ECHO} '$${SUBDIR} contains "unknown"; possibly you have an unsupported system.'
	@${ECHO} 'See shared/mk/tendra.makedefs.mk for supported systems.'
	@${EXIT} 1;
.endif


.if !empty(SUBDIR)
# Just in case there happens to be a target of the same name.
.PHONY: ${SUBDIR}

# Proceed to subdirs.
. for target in all doc clean install install-doc
${target}::
.  for entry in ${SUBDIR}
	@cd ${.CURDIR}/${entry}; ${MAKE} ${.TARGET}
.  endfor
. endfor
.endif



.endif	# !defined(_TENDRA_SUBDIR_MK_)
