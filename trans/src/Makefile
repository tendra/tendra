# $Id$

.include "Makefile.inc"

.include <tendra.base.mk>
.include <tendra.makedefs.mk>


.if !defined(ALLARCH)
SUBDIR+=	${TRANSARCH}
.else
SUBDIR+=	680x0
SUBDIR+=	80x86
SUBDIR+=	alpha
SUBDIR+=	hppa
SUBDIR+=	mips
SUBDIR+=	power
SUBDIR+=	sparc
SUBDIR+=	stub
.endif

.include <tendra.subdir.mk>

