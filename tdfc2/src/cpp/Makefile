# $Id$

.include "Makefile.inc"


#SUBDIR+=	lpi
#SUBDIR+=	stdlib

#.include <tendra.subdir.mk>



# TODO: centralise this
${OBJ_SDIR}:
	${MKDIR} -p ${.TARGET}


PART_CFLAGS+=	-I ${BASE_DIR}/src/cpp

PARTS+=	src/common/construct
PARTS+=	src/common/utility
PARTS+=	src/common/obj_c
PARTS+=	src/common/output
PARTS+=	src/common/parse
PARTS+=	src/common/spec
PARTS+=	src/common/shared
PARTS+=	src/common/tdf
PARTS+=	src/common

PARTS+=	src/cpp/syntax

.include <tendra.partial.mk>


PROG=    	tcpplus
EXEC_BIN=	${PREFIX_LIBEXEC}

.include <tendra.prog.mk>

