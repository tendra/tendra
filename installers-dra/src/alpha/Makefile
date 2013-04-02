# $Id$

.include "Makefile.inc"


#TCCOPTS=-Xc -Y32bit -Yansi

PART_CFLAGS+=	-D TRANS_ALPHA

# XXX: the Alpha code currently assumes BLDARCHBITS is 64.
# Some parts use the INT64 abstraction; others do not. Until that's sorted
# out, I'm lying about BLDARCHBITS here, just so this code isn't left out
# of the build under -DALLARCH.
#PART_CFLAGS+=	-D BLDARCHBITS=${BLDARCHBITS}
PART_CFLAGS+=	-D BLDARCHBITS=64

PART_CFLAGS+=	-I ${BASE_DIR}/src/common
PART_CFLAGS+=	-I ${BASE_DIR}/src/alpha/common

PARTS+=	src/common/shared
PARTS+=	src/common/construct
PARTS+=	src/common/diag
PARTS+=	src/common/linkinfo
PARTS+=	src/common/reader
PARTS+=	src/common/refactor
PARTS+=	src/alpha/common

.include <tendra.partial.mk>


PROG=    	trans.${.CURDIR:T}
EXEC_BIN=	${PREFIX_LIBEXEC}

.include <tendra.prog.mk>

