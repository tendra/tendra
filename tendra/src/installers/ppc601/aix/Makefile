# $Id$

.include "Makefile.inc"


#TCCOPTS=-Xc -Y32bit -Yansi

# note power/, not ppc601/
PART_CFLAGS+=	-I ${BASE_DIR}/src/installers/power/common
PART_CFLAGS+=	-I ${BASE_DIR}/src/installers/power/aix

# note power/, not ppc601/
PARTS+=	src/installers/common/construct
PARTS+=	src/installers/common/diag
PARTS+=	src/installers/common/linkinfo
PARTS+=	src/installers/common/reader
PARTS+=	src/installers/power/common
PARTS+=	src/installers/power/aix

.include <tendra.partial.mk>


PROG=	trans

.include <tendra.prog.mk>

