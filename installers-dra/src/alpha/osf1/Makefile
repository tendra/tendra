# $Id$

.include "Makefile.inc"


#TCCOPTS=-Xc -Y32bit -Yansi

PART_CFLAGS+=	-I ${BASE_DIR}/src/common/shared/error
PART_CFLAGS+=	-I ${BASE_DIR}/src/common/shared/xalloc
PART_CFLAGS+=	-I ${BASE_DIR}/src/common/construct
PART_CFLAGS+=	-I ${BASE_DIR}/src/common/diag
PART_CFLAGS+=	-I ${BASE_DIR}/src/common/linkinfo
PART_CFLAGS+=	-I ${BASE_DIR}/src/common/reader
PART_CFLAGS+=	-I ${BASE_DIR}/src/alpha/common
PART_CFLAGS+=	-I ${BASE_DIR}/src/alpha/osf1

PARTS+=	src/common/shared/error
PARTS+=	src/common/shared/xalloc
PARTS+=	src/common/construct
PARTS+=	src/common/diag
PARTS+=	src/common/linkinfo
PARTS+=	src/common/reader
PARTS+=	src/alpha/common

.include <tendra.partial.mk>


PROG=    	trans.${.CURDIR:H:T}.${.CURDIR:T}
EXEC_BIN=	${PREFIX_LIBEXEC}

.include <tendra.prog.mk>

