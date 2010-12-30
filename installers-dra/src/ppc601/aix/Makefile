# $Id$

.include "Makefile.inc"


#TCCOPTS=-Xc -Y32bit -Yansi

# note power/, not ppc601/
PART_CFLAGS+=	-I ${BASE_DIR}/src/power/common
PART_CFLAGS+=	-I ${BASE_DIR}/src/power/aix

# note power/, not ppc601/
PARTS+=	src/common/construct
PARTS+=	src/common/diag
PARTS+=	src/common/linkinfo
PARTS+=	src/common/reader
PARTS+=	src/power/common
PARTS+=	src/power/aix

.include <tendra.partial.mk>


PROG=    	trans.${BLDARCH}
EXEC_BIN=	${PREFIX_LIBEXEC}

.include <tendra.prog.mk>

