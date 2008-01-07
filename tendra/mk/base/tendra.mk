# $TenDRA$
#

.if !defined(SRC_DIR)
SRC_DIR=	${.CURDIR:C/(.*)\/src.*/\1/}
.endif

.if !exists (${SRC_DIR}/config.mk)

.MAIN: all

all: config-check _PROGSUBDIR

.endif

.include "tendra.subdir.mk"

.include "tendra.config.mk"
