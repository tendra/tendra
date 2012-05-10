# $Id$

.include "Makefile.inc"

.include <tendra.base.mk>


.if !defined(ALLARCH)
SUBDIR+=	${OSFAM}
.else
SUBDIR+=	aix
SUBDIR+=	openbsd
.endif

.include <tendra.subdir.mk>

