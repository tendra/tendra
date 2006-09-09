# $TenDRA$

ADA_DIR = ${.CURDIR:C/(.*)\/tdfada.*/\1/}

.SUFFIXES : .adb .ads

.PATH.ads : ${.CURDIR} ${ADA_DIR}/asis ${ADA_DIR}/libgela ${ADA_DIR}/xasis
.PATH.adb : ${.CURDIR} ${ADA_DIR}/asis ${ADA_DIR}/libgela ${ADA_DIR}/xasis

.if !defined(SRC_DIR)
SRC_DIR = ${.CURDIR:C/(.*)\/src.*/\1/}
.endif

ADA_DIR = ${.CURDIR:C/(.*)\/tdfada.*/\1/}

ADA_PROG = tdfada
LDFLAGS = -bargs -E
TENDRA_TYPES = tendra-types.ads tendra-types.adb

MAKE_TDF = ../../../make_tdf/make_tdf
TDF_DB   = ${SRC_DIR}/src/lib/tdf/def_4_0.db

${TENDRA_TYPES}: $(TDF_DB) tendra-types.ad[sb].tdf
	$(MAKE_TDF) $(TDF_DB) ${.CURDIR}/tendra-types.ads.tdf tendra-types.ads
	$(MAKE_TDF) $(TDF_DB) ${.CURDIR}/tendra-types.adb.tdf tendra-types.adb

CFLAGS=-m -g -O
CFLAGS+= -I${.CURDIR}
CFLAGS+= -I../asis
CFLAGS+= -I${ADA_DIR}/asis
CFLAGS+= -I${ADA_DIR}/xasis
CFLAGS+= -I${ADA_DIR}/libgela

DEPEND_SRC  = *.ad[sb] ${TENDRA_TYPES}

CLEANFILES=*

.include "${.CURDIR}/../../../../mk/base/tendra.prog.mk"
