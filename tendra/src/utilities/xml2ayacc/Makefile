# $TenDRA:  $

.if !defined(SRC_DIR)
SRC_DIR=        ${.CURDIR:C/(.*)\/src.*/\1/}
.endif

.if exists (${SRC_DIR}/config.mk)
.include "${SRC_DIR}/config.mk"
.endif


.if defined(WITH_ADA)
ADA_DIR= ${SRC_DIR}/src/producers/ada

CFLAGS+= -g -O -I${.CURDIR}
CFLAGS+= -I${ADA_DIR}/libgela
CFLAGS+= -I${ADA_DIR}/encoding
CFLAGS+= -I${ADA_DIR}/encoding/auto
CFLAGS+= -I${ADA_DIR}/xml_io

.PATH : ${.CURDIR} .

ADA_PROG = xml_to_y
DONT_INSTALL = Y

CLEANFILES=*

.include "${.CURDIR}/../../../mk/base/tendra.prog.mk"

.else
install:

make-subdir:

clean:

.endif
