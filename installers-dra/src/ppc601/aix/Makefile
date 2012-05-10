# $Id$

.include "Makefile.inc"


#TCCOPTS=-Xc -Y32bit -Yansi

# note power/, not ppc601/
PART_CFLAGS+=	-I ${BASE_DIR}/src/common/linkinfo
PART_CFLAGS+=	-I ${BASE_DIR}/src/power/common

# note ppc601
PART_CFLAGS+=	-I ${BASE_DIR}/src/ppc601/aix

# note power/, not ppc601/
PARTS+=	src/common/shared
PARTS+=	src/common/construct
PARTS+=	src/common/diag
PARTS+=	src/common/linkinfo
PARTS+=	src/common/reader
PARTS+=	src/power/common

.include <tendra.partial.mk>


PROG=    	trans.${.CURDIR:H:T}.${.CURDIR:T}
EXEC_BIN=	${PREFIX_LIBEXEC}

.include <tendra.prog.mk>

