# $Id$

.include "Makefile.inc"

.include <tendra.base.mk>


.if exists(${OSFAM})
SUBDIR+=	${OSFAM}
.endif

.if defined(GLIBC_NAME)
.if exists(${GLIBC_NAME:tl})
SUBDIR+=	${GLIBC_NAME:tl}
.endif
.endif

.include <tendra.subdir.mk>

