# $Id$

.include "Makefile.inc"

.include <tendra.base.mk>


.if !defined(ALLARCH)
SUBDIR+=	${BLDARCH}
.else
SUBDIR+=	680x0
SUBDIR+=	80x86
SUBDIR+=	alpha
SUBDIR+=	hppa
SUBDIR+=	mips
SUBDIR+=	power
SUBDIR+=	sparc
.endif

.include <tendra.subdir.mk>

