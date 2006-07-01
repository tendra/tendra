# $TenDRA:  $

.if !defined(SRC_DIR)
SRC_DIR=        ${.CURDIR:C/(.*)\/src.*/\1/}
.endif

.if exists (${SRC_DIR}/config.mk)
.include "${SRC_DIR}/config.mk"
.endif


.if defined(WITH_ADA)

SUBDIR= asis tdfada

.include "${.CURDIR}/../../../mk/base/tendra.subdir.mk"

.else

install:

make-subdir:

clean:

.endif
