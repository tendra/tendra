# $Id$

.include "Makefile.inc"


#TCCOPTS=	-Xc -Y32bit -Yposix

PART_CFLAGS+=	-I ${BASE_DIR}/src/installers/680x0/common
PART_CFLAGS+=	-I ${BASE_DIR}/src/installers/680x0/sunos

PARTS+= src/installers/common/construct
PARTS+= src/installers/common/diag
PARTS+= src/installers/common/reader
PARTS+= src/installers/680x0/common

.include <tendra.partial.mk>


SRCS+=	main.c

.include <tendra.obj.mk>


EXEC_BIN=	${MACH_BASE}/bin

PROG=	trans

.include <tendra.prog.mk>

