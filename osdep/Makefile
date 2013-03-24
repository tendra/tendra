# $Id$

.include "Makefile.inc"


.if !defined(WEBSITE)
SUBDIR+=	machines
SUBDIR+=	arch
SUBDIR+=	src
.endif

.if !defined(NOTESTS)
SUBDIR+=	tests
.endif

.if defined(WITHDOCS)
SUBDIR+=	doc
.endif

.include <tendra.subdir.mk>

