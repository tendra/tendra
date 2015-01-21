# $Id$

.include "Makefile.inc"

.include <tendra.base.mk>
.include <tendra.makedefs.mk>


.if exists(${BLDARCH})
SUBDIR+=	${BLDARCH}
.endif

.if exists(${TRANSARCH})
SUBDIR+=	${TRANSARCH}
.endif

.include <tendra.subdir.mk>

