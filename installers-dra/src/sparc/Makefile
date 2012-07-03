# $Id$

.include "Makefile.inc"

.include <tendra.base.mk>


.if !defined(ALLARCH)
SUBDIR+=	${OSFAM}
.else
SUBDIR+=	linux
SUBDIR+=	openbsd
SUBDIR+=	solaris
SUBDIR+=	sunos
.endif

.include <tendra.subdir.mk>

