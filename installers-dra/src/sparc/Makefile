# $Id$

.include "Makefile.inc"


.if !defined(ALLARCH)
SUBDIR+=	${OSFAM}
.else
SUBDIR+=	openbsd
SUBDIR+=	solaris
SUBDIR+=	sunos
.endif

.include <tendra.subdir.mk>

