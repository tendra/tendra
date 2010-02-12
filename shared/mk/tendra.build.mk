# TenDRA make build infrastructure
#
# $Id$

.if !defined(_TENDRA_BUILD_MK_)
_TENDRA_BUILD_MK_=1

.include <tendra.base.mk>
.include <tendra.functions.mk>
.include <tendra.rules.mk>

# Do some pretty-printing.
WRKDIR=		${.CURDIR:C/^${BASE_DIR}\///1}

# The main target is synthetised based upon actual needs.
.if !target(.MAIN)
.MAIN: all
.endif


# Suppport targets.

# Remove registered garbage.
clean::
	@${ECHO} "==> Cleaning ${.CURDIR}"
.if "${CLEAN_EXTRA}" != ""
	${REMOVE} ${CLEAN_EXTRA}
.endif

# Clean objdir blindly.
cleandir::
.if "${_objdir}" != ""
	${REMOVE} -r ${_objdir}/* 2> /dev/null
.endif

# Remove obj symlink from curdir.
cleanobj::
.if "${_objdir}" != ""
	@if ${TEST} -h ${.CURDIR}/obj ; then \
		${ECHO} "==> Removing obj link ${WRKDIR}/obj" ; \
		${REMOVE} ${.CURDIR}/obj ; \
		${REMOVE} ${OBJ_DIR_INDICATOR} 2> /dev/null ; \
	fi
.endif

# Create objdir and its symlink.
obj::
.if "${_objdir}" != ""
. if !exists(${_objdir})
	@${ECHO} "==> Creating objdir ${_objdir}"
	@${MKDIR} -p ${_objdir}
. endif
. if "${.CURDIR}/obj" != "${_objdir}"
	@${REMOVE} ${.CURDIR}/obj
	@${LN} -sf ${_objdir} ${.CURDIR}/obj
. endif
.endif


# Make sure subdirs are walked after real work is done.
.ORDER: _REALWORK _SUBDIR

.endif	# !defined(_TENDRA_BUILD_MK_)
