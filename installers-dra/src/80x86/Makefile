# $Id$

.include "Makefile.inc"

.include <tendra.base.mk>


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

