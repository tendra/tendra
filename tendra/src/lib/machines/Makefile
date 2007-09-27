# $Id$

.include "../../../Makefile.defs"

.if "${OSFAM}" == "openbsd" || "${OSFAM}" == "linux" || "${OSFAM}" == "netbsd"
SUBDIR = ${OSFAM}
.else

MACHSUBDIR:= ${OSFAM}/${BLDARCH}

.if exists(${MACHSUBDIR}/src)
SUBDIR=	${MACHSUBDIR}/src
.endif

SUBDIR+= ${MACHSUBDIR}/tokens

.endif

.include "Makefile.inc"
