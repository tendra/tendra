# $Id$

.include "Makefile.inc"


#TCCOPTS=       -Xc -Y32bit -Yansi

PART_CFLAGS+=	-I ${BASE_DIR}/src/installers/80x86/common
PART_CFLAGS+=	-I ${BASE_DIR}/src/installers/80x86/solaris

PARTS+= src/installers/common/construct
PARTS+= src/installers/common/diag
PARTS+= src/installers/common/dwarf2
PARTS+= src/installers/common/linkinfo
PARTS+= src/installers/common/reader
PARTS+= src/installers/80x86/common

.include <tendra.partial.mk>


CFLAGS+=	-I ../../common/construct
CFLAGS+=	-I ../../common/diag
CFLAGS+=	-I ../../common/dwarf2
CFLAGS+=	-I ../../common/linkinfo
CFLAGS+=	-I ../../common/reader
CFLAGS+=	-I ../common
CFLAGS+=	-I .

SRCS+=	assembler.c
SRCS+=	diag_out.c
SRCS+=	dw2_config.c
SRCS+=	machine.c

.include <tendra.obj.mk>


EXEC_BIN=	${MACH_BASE}/bin

PROG=	trans

.include <tendra.prog.mk>

