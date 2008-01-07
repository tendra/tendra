# $TenDRA$

# Platform settings.
PREFIX?=	/usr/local
MAN_COMPRESS=	yes
MAN_INSTALL=	yes
TMP_DIR=	/tmp
NO_RANLIB=	yes

# SRC_ENV corresponds to the hierarchy in tendra/src/lib/env.
PREFIX?=	/usr/local
TMP_DIR=	/tmp
SRC_ENV=	${BUILD_OS}/common/${MACH_CPU}

MACH_CPU!=	${BIN_UNAME} -p
MACH_OS!=	${BIN_UNAME}
MACH_VERS!=	${BIN_UNAME} -r

.if ${MACH_OS} == "IRIX64"
MACH_OS=       IRIX
.endif

# Not sure of the best way to get the exec type, suggestions?
MACH_EXEC=	elf

.include "config.common.mk"
