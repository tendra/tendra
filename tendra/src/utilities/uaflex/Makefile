# $TenDRA:  $

.if !defined(SRC_DIR)
SRC_DIR=        ${.CURDIR:C/(.*)\/src.*/\1/}
.endif

.if exists (${SRC_DIR}/config.mk)
.include "${SRC_DIR}/config.mk"
.endif


.if defined(WITH_ADA)
ADA_DIR= ${SRC_DIR}/src/producers/ada

CFLAGS+= -I${.CURDIR}

.PATH : ${.CURDIR} .

ADA_PROG = uaflex
DONT_INSTALL = Y

CLEANFILES=*

.include "${.CURDIR}/../../../mk/base/tendra.prog.mk"

.else
install:

make-subdir:

clean:

.endif
