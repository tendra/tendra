# $Id$

.include "Makefile.inc"


#TCCOPTS=-Xc -Y32bit -Yansi

PART_CFLAGS+=	-I ${BASE_DIR}/src/common/shared
PART_CFLAGS+=	-I ${BASE_DIR}/src/common/linkinfo
PART_CFLAGS+=	-I ${BASE_DIR}/src/power/common
PART_CFLAGS+=	-I ${BASE_DIR}/src/power/aix

PARTS+=	src/common/shared/error
PARTS+=	src/common/shared/xalloc
PARTS+=	src/common/construct
PARTS+=	src/common/diag
PARTS+=	src/common/linkinfo
PARTS+=	src/common/reader
PARTS+=	src/power/common

.include <tendra.partial.mk>


PROG=    	trans.${.CURDIR:H:T}.${.CURDIR:T}
EXEC_BIN=	${PREFIX_LIBEXEC}

.include <tendra.prog.mk>

