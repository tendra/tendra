# $Id$

SUBDIR=	common

.include "../../../Makefile.defs"
.include "../../../mk/tendra.base.mk"

ENVSUBDIR=	${OSFAM}/common/common ${OSFAM}/common/${BLDARCH}\
		${OSFAM}/${EXECFORMAT}/common ${OSFAM}/${EXECFORMAT}/${BLDARCH}\
		${OSFAM}/${OSVER}/common ${OSFAM}/${OSVER}/${BLDARCH}

.for environ in ${ENVSUBDIR}
. if exists(${environ})
SUBDIR+=${environ}
. endif
.endfor

.include "Makefile.inc"
