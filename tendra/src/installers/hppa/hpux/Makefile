# $Id$

.include "Makefile.inc"


#TCCOPTS=-Xc -Y32bit -Yansi

PART_CFLAGS+=	-I ${BASE_DIR}/src/installers/hppa/common
PART_CFLAGS+=	-I ${BASE_DIR}/src/installers/hppa/hpux

PARTS+=	src/installers/common/construct
PARTS+=	src/installers/common/diag
PARTS+=	src/installers/common/linkinfo
PARTS+=	src/installers/common/reader
PARTS+=	src/installers/hppa/common

.include <tendra.partial.mk>


SRCS+=	hppatrans.c

.include <tendra.obj.mk>


EXEC_BIN=	${MACH_BASE}/bin

PROG=	trans

.include <tendra.prog.mk>

