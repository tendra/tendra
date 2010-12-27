# $Id$

# TCCOPTS=	-Yposix1 -Xs

.include "Makefile.inc"


# TODO: centralise this
${OBJ_SDIR}:
	${MKDIR} -p ${.TARGET}


PART_CFLAGS+=	-I ${BASE_DIR}/src/c/syntax

PARTS+=	src/common/construct
PARTS+=	src/common/utility
PARTS+=	src/common/obj_c
PARTS+=	src/common/output
PARTS+=	src/common/parse
PARTS+=	src/common

PARTS+=	src/c/syntax

.include <tendra.partial.mk>


PROG=    	tdfc2
EXEC_BIN=	${LIBEXEC_DIR}

.include <tendra.prog.mk>

