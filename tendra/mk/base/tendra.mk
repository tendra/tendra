# $TenDRA$
#

SRC_DIR=	${.CURDIR:C/(.*)\/src.*/\1/}

.if !exists (${SRC_DIR}/config.mk)

.MAIN: all

all: config-check _PROGSUBDIR

.endif

.include "tendra.subdir.mk"

.include "tendra.config.mk"
