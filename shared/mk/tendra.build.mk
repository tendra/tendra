# TenDRA make build infrastructure
#
# $Id$

.if !defined(_TENDRA_BUILD_MK_)
_TENDRA_BUILD_MK_=1

.include <tendra.base.mk>
.include <tendra.functions.mk>

# Do some pretty-printing.
WRKDIR=		${.CURDIR:C/^${BASE_DIR}\///1}

# The main target is synthetised based upon actual needs.
.if !target(.MAIN)
.MAIN: all
.endif


# Make sure subdirs are walked after real work is done.
.ORDER: _REALWORK _SUBDIR

.endif	# !defined(_TENDRA_BUILD_MK_)
