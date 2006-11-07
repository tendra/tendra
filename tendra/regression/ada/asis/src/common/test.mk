
SRC_DIR	=       ${.CURDIR:C/(.*)\/regression.*/\1/}

ADA_DIR	= ${SRC_DIR}/src/producers/ada
LIB_DIR	= ${SRC_DIR}/obj/producers/ada/asis

CFLAGS+= -g -m -O -I${.CURDIR}
CFLAGS+= -I${.CURDIR}/../common
CFLAGS+= -I${LIB_DIR}
CFLAGS+= -I${ADA_DIR}/asis
CFLAGS+= -I${ADA_DIR}/xasis
CFLAGS+= -I${ADA_DIR}/libgela

ADA_SRC ?= run.adb
DONT_INSTALL = Y

DEPEND_SRC = ${LIB_DIR}/libasis.a

CLEANFILES=*

.include "${SRC_DIR}/mk/base/tendra.prog.mk"
