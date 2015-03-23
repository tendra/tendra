# $Id$

TCCOPTS=	-Yposix

.include "Makefile.inc"


# TODO: centralise this
${OBJ_SDIR}:
	${MKDIR} -p ${.TARGET}


PART_CFLAGS+=	-I ${BASE_DIR}/src/c

PARTS+=	src/common/construct
PARTS+=	src/common/utility
PARTS+=	src/common/obj_c
PARTS+=	src/common/output
PARTS+=	src/common/parse
PARTS+=	src/common/spec
PARTS+=	src/common/shared
PARTS+=	src/common

PARTS+=	src/c/syntax

.include <tendra.partial.mk>


PROG=    	tdfc2
EXEC_BIN=	${PREFIX_LIBEXEC}

.include <tendra.prog.mk>

