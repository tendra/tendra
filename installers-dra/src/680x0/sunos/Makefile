# $Id$

.include "Makefile.inc"


#TCCOPTS=	-Xc -Y32bit -Yposix

PART_CFLAGS+=	-I ${BASE_DIR}/src/common/shared/error
PART_CFLAGS+=	-I ${BASE_DIR}/src/common/shared/xalloc
PART_CFLAGS+=	-I ${BASE_DIR}/src/680x0/common
PART_CFLAGS+=	-I ${BASE_DIR}/src/680x0/sunos

PARTS+= src/common/shared/error
PARTS+= src/common/shared/xalloc
PARTS+= src/common/construct
PARTS+= src/common/diag
PARTS+= src/common/linkinfo
PARTS+= src/common/reader
PARTS+= src/680x0/common

.include <tendra.partial.mk>


PROG=    	trans.${.CURDIR:H:T}.${.CURDIR:T}
EXEC_BIN=	${PREFIX_LIBEXEC}

.include <tendra.prog.mk>

