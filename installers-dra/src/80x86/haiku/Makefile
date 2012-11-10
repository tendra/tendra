# $Id: Makefile 2493 2010-12-30 01:38:37Z kate $

.include "Makefile.inc"


#TCCOPTS=	-Xc -Y32bit -Yansi

PART_CFLAGS+=	-I ${BASE_DIR}/src/80x86/common
PART_CFLAGS+=	-I ${BASE_DIR}/src/80x86/haiku

PARTS+= src/common/shared
PARTS+= src/common/construct
PARTS+= src/common/diag
PARTS+= src/common/linkinfo
PARTS+= src/common/reader
PARTS+= src/common/refactor
PARTS+= src/80x86/common

.include <tendra.partial.mk>


CFLAGS+=	-I ../../common
CFLAGS+=	-I ../common
CFLAGS+=	-I .

SRCS+=	diag_out.c
SRCS+=	machine.c

.include <tendra.obj.mk>


PROG=    	trans.${.CURDIR:H:T}.${.CURDIR:T}
EXEC_BIN=	${PREFIX_LIBEXEC}

.include <tendra.prog.mk>

