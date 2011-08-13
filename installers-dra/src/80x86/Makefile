# $Id$

.include "Makefile.inc"


.if !defined(ALLARCH)
SUBDIR+=	${OSFAM}
.else
SUBDIR+=	dragonfly
SUBDIR+=	freebsd
SUBDIR+=	haiku
SUBDIR+=	linux
SUBDIR+=	netbsd
SUBDIR+=	openbsd
SUBDIR+=	solaris
.endif

.include <tendra.subdir.mk>

