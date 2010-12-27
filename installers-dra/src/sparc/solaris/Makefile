# $Id$

.include "Makefile.inc"


#TCCOPTS=-Xc -Y32bit -Yansi

PART_CFLAGS+=	-I ${BASE_DIR}/src/sparc/common
PART_CFLAGS+=	-I ${BASE_DIR}/src/sparc/solaris

PARTS+=	src/common/construct
PARTS+=	src/common/diag
PARTS+=	src/common/dwarf2
PARTS+=	src/common/linkinfo
PARTS+=	src/common/reader
PARTS+=	src/sparc/common

.include <tendra.partial.mk>


SRCS+=	dw2_config.c
SRCS+=	sparcdiags.c

.include <tendra.obj.mk>


PROG=    	trans.${BLDARCH}
EXEC_BIN=	${LIBEXEC_DIR}

.include <tendra.prog.mk>

