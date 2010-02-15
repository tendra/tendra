# $Id$

.include "Makefile.inc"


#TCCOPTS=-Xc -Y32bit -Yansi

PART_CFLAGS+=	-I ${BASE_DIR}/src/installers/sparc/common
PART_CFLAGS+=	-I ${BASE_DIR}/src/installers/sparc/solaris

PARTS+=	src/installers/common/construct
PARTS+=	src/installers/common/diag
PARTS+=	src/installers/common/dwarf2
PARTS+=	src/installers/common/linkinfo
PARTS+=	src/installers/common/reader
PARTS+=	src/installers/sparc/common

.include <tendra.partial.mk>


SRCS+=	dw2_config.c
SRCS+=	sparcdiags.c

.include <tendra.obj.mk>


EXEC_BIN=	${MACH_BASE}/bin

PROG=	trans

.include <tendra.prog.mk>

