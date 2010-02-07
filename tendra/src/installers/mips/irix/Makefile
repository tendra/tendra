# $Id$

.include "Makefile.inc"

#TCCOPTS=-Xc -Y32bit -Yansi

PART_CFLAGS+=	-I ${BASE_DIR}/src/installers/mips/common
PART_CFLAGS+=	-I ${BASE_DIR}/src/installers/mips/irix

PARTS+=	src/installers/common/construct
PARTS+=	src/installers/common/diag
PARTS+=	src/installers/common/linkinfo
PARTS+=	src/installers/common/reader
PARTS+=	src/installers/mips/common

.include <tendra.partial.mk>


SRCS+=	main.c
SRCS+=	out_ba.c

.include <tendra.obj.mk>


PROG=	trans

.include <tendra.prog.mk>

