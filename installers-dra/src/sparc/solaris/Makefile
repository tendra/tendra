# $Id$

.include "Makefile.inc"


#TCCOPTS=-Xc -Y32bit -Yansi

PART_CFLAGS+=	-D TRANS_SPARC
PART_CFLAGS+=	-D BLDARCHBITS=${BLDARCHBITS}

PART_CFLAGS+=	-I ${BASE_DIR}/src/sparc/common
PART_CFLAGS+=	-I ${BASE_DIR}/src/sparc/solaris

PARTS+=	src/common/shared
PARTS+=	src/common/construct
PARTS+=	src/common/newdiag
PARTS+=	src/common/dwarf2
PARTS+=	src/common/linkinfo
PARTS+=	src/common/reader
PARTS+=	src/common/refactor
PARTS+=	src/sparc/common

.include <tendra.partial.mk>


PROG=    	trans.${.CURDIR:H:T}.${.CURDIR:T}
EXEC_BIN=	${PREFIX_LIBEXEC}

.include <tendra.prog.mk>

