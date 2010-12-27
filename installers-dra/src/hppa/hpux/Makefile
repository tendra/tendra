# $Id$

.include "Makefile.inc"


#TCCOPTS=-Xc -Y32bit -Yansi

PART_CFLAGS+=	-I ${BASE_DIR}/src/hppa/common
PART_CFLAGS+=	-I ${BASE_DIR}/src/hppa/hpux

PARTS+=	src/common/construct
PARTS+=	src/common/diag
PARTS+=	src/common/linkinfo
PARTS+=	src/common/reader
PARTS+=	src/hppa/common

.include <tendra.partial.mk>


SRCS+=	hppatrans.c

.include <tendra.obj.mk>


PROG=	trans

.include <tendra.prog.mk>

