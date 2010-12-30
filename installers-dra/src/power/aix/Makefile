# $Id$

.include "Makefile.inc"


#TCCOPTS=-Xc -Y32bit -Yansi

PART_CFLAGS+=	-I ${BASE_DIR}/src/power/common
PART_CFLAGS+=	-I ${BASE_DIR}/src/power/aix

PARTS+=	src/common/construct
PARTS+=	src/common/diag
PARTS+=	src/common/linkinfo
PARTS+=	src/common/reader
PARTS+=	src/power/common

.include <tendra.partial.mk>


SRCS+=	powertrans.c

.include <tendra.obj.mk>


PROG=    	trans.${BLDARCH}
EXEC_BIN=	${PREFIX_LIBEXEC}

.include <tendra.prog.mk>

