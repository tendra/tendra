# $Id$

.include "Makefile.inc"


#TCCOPTS=	-Xc -Y32bit -Yansi

PART_CFLAGS+=	-I ${BASE_DIR}/src/common/shared/error
PART_CFLAGS+=	-I ${BASE_DIR}/src/common/shared/xalloc
PART_CFLAGS+=	-I ${BASE_DIR}/src/80x86/common
PART_CFLAGS+=	-I ${BASE_DIR}/src/80x86/freebsd

PARTS+= src/common/shared/error
PARTS+= src/common/shared/xalloc
PARTS+= src/common/construct
PARTS+= src/common/diag
PARTS+= src/common/linkinfo
PARTS+= src/common/reader
PARTS+= src/80x86/common

.include <tendra.partial.mk>


CFLAGS+=	-I ../../common/shared/error
CFLAGS+=	-I ../../common/shared/xalloc
CFLAGS+=	-I ../../common/construct
CFLAGS+=	-I ../../common/diag
CFLAGS+=	-I ../../common/linkinfo
CFLAGS+=	-I ../../common/reader
CFLAGS+=	-I ../common
CFLAGS+=	-I .

SRCS+=	assembler.c
SRCS+=	diag_out.c
SRCS+=	machine.c

.include <tendra.obj.mk>


PROG=    	trans.${.CURDIR:H:T}.${.CURDIR:T}
EXEC_BIN=	${PREFIX_LIBEXEC}

.include <tendra.prog.mk>

