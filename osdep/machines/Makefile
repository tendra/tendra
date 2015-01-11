# $Id$

.include "Makefile.inc"

.include <tendra.base.mk>
.include <tendra.makedefs.mk>


SUBDIR+=	common
SUBDIR+=	${OSFAM}

.if "${LIBCFAM}" != "${OSFAM}"
. if exists(${LIBCFAM})
SUBDIR+=        ${LIBCFAM}
. endif
.endif

.include <tendra.subdir.mk>

