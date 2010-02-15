# $Id$

.include "Makefile.inc"


#TCCOPTS=-Xc -Y32bit -Yansi

PART_CFLAGS+=	-I ${BASE_DIR}/src/installers/power/common
PART_CFLAGS+=	-I ${BASE_DIR}/src/installers/power/aix

PARTS+=	src/installers/common/construct
PARTS+=	src/installers/common/diag
PARTS+=	src/installers/common/linkinfo
PARTS+=	src/installers/common/reader
PARTS+=	src/installers/power/common

.include <tendra.partial.mk>


SRCS+=	powertrans.c

.include <tendra.obj.mk>


EXEC_BIN=	${MACH_BASE}/bin

PROG=	trans

.include <tendra.prog.mk>

