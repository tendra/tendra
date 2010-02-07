# $Id$

# TCCOPTS=      -Yposix1 -Xs

.include "Makefile.inc"


# TODO: centralise this
${OBJ_SDIR}:
	${MKDIR} -p ${.TARGET}


PART_CFLAGS+=	-I ${BASE_DIR}/src/producers/cpp/syntax

PARTS+=	src/producers/common/construct
PARTS+=	src/producers/common/utility
PARTS+=	src/producers/common/obj_c
PARTS+=	src/producers/common/output
PARTS+=	src/producers/common/parse
PARTS+=	src/producers/common

PARTS+=	src/producers/cpp/syntax

.include <tendra.partial.mk>


PROG=	tcpplus

.include <tendra.prog.mk>

