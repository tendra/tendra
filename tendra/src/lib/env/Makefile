# $Id$

SUBDIR= common

.include "../../../Makefile.defs"
.include "../../../mk/tendra.base.mk"

.if exists(${OSFAM}/common/common)
SUBDIR+=	${OSFAM}/common/common
.endif
.if exists(${OSFAM}/common/${BLDARCH})
SUBDIR+=	${OSFAM}/common/${BLDARCH}
.endif
.if exists(${OSFAM}/common/${BLDARCH})
SUBDIR+=	${OSFAM}/${EXECFORMAT}/common
.endif
.if exists(${OSFAM}/common/${BLDARCH})
SUBDIR+=	${OSFAM}/${EXECFORMAT}/${BLDARCH}
.endif
.if exists(${OSFAM}/common/${BLDARCH})
SUBDIR+=	${OSFAM}/${OSVER}/common
.endif
.if exists(${OSFAM}/common/${BLDARCH})
SUBDIR+=	${OSFAM}/${OSVER}/${BLDARCH}
.endif

.include "Makefile.inc"
