# $Id$

.include "Makefile.inc"


#TCCOPTS=-Xc -Y32bit -Yansi

PART_CFLAGS+=	-I ${BASE_DIR}/src/common/shared
PART_CFLAGS+=	-I ${BASE_DIR}/src/sparc/common
PART_CFLAGS+=	-I ${BASE_DIR}/src/sparc/openbsd

PARTS+=	src/common/shared/error
PARTS+=	src/common/shared/xalloc
PARTS+=	src/common/construct
PARTS+=	src/common/diag
PARTS+=	src/common/dwarf2
PARTS+=	src/common/linkinfo
PARTS+=	src/common/reader
PARTS+=	src/sparc/common

.include <tendra.partial.mk>


CFLAGS+=	-I ../../common/shared
CFLAGS+=	-I ../../common/construct
CFLAGS+=	-I ../../common/diag
CFLAGS+=	-I ../../common/linkinfo
CFLAGS+=	-I ../../common/reader
CFLAGS+=	-I ../common
CFLAGS+=	-I .

SRCS+=	dw2_config.c
SRCS+=	sparcdiags.c

.include <tendra.obj.mk>


PROG=    	trans.${.CURDIR:H:T}.${.CURDIR:T}
EXEC_BIN=	${PREFIX_LIBEXEC}

.include <tendra.prog.mk>

