# $Id$

.include "Makefile.inc"


#TCCOPTS=-Xc -Y32bit -Yansi

PART_CFLAGS+=	-I ${BASE_DIR}/src/installers/alpha/common
PART_CFLAGS+=	-I ${BASE_DIR}/src/installers/alpha/osf1

PARTS+=	src/installers/common/construct
PARTS+=	src/installers/common/diag
PARTS+=	src/installers/common/linkinfo
PARTS+=	src/installers/common/reader
PARTS+=	src/installers/alpha/common

.include <tendra.partial.mk>


SRCS+=	driver.c

.include <tendra.obj.mk>


EXEC_BIN=	${MACH_BASE}/bin

PROG=	trans

.include <tendra.prog.mk>

