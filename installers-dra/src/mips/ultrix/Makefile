# $Id$

.include "Makefile.inc"


#TCCOPTS=-Xc -Y32bit -Yansi

PART_CFLAGS+=	-I ${BASE_DIR}/src/mips/common
PART_CFLAGS+=	-I ${BASE_DIR}/src/mips/irix

PARTS+=	src/common/construct
PARTS+=	src/common/diag
PARTS+=	src/common/linkinfo
PARTS+=	src/common/reader
PARTS+=	src/mips/common

.include <tendra.partial.mk>


SRCS+=	main.c
SRCS+=	out_ba.c

.include <tendra.obj.mk>


PROG=    	trans.${BLDARCH}
EXEC_BIN=	${PREFIX_LIBEXEC}

.include <tendra.prog.mk>

