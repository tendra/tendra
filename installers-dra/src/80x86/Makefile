# $Id$

.include "Makefile.inc"


#TCCOPTS=	-Xc -Y32bit -Yansi

PART_CFLAGS+=	-D TRANS_80x86
PART_CFLAGS+=	-D BLDARCHBITS=${BLDARCHBITS}

PART_CFLAGS+=	-I ${BASE_DIR}/src/80x86/common

# TODO: these are not yet selectable at runtime
# -D NEWDIAGS
# -D NEWDWARF

PARTS+= src/common/shared
PARTS+= src/common/construct
PARTS+= src/common/diag
PARTS+= src/common/linkinfo
PARTS+= src/common/reader
PARTS+= src/common/refactor
PARTS+= src/80x86/common

.include <tendra.partial.mk>


PROG=    	trans.${.CURDIR:T}
EXEC_BIN=	${PREFIX_LIBEXEC}

.include <tendra.prog.mk>

