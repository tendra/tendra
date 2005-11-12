# $TenDRA$

# Platform settings.
PREFIX?=	/usr/local
MAN_COMPRESS=	yes
MAN_INSTALL=	yes
TMP_DIR=	/tmp


# SRC_ENV corresponds to the hierarchy in tendra/src/lib/env.
SRC_ENV=	${BUILD_OS}/common/${MACH_CPU}

TMP_CPU!=	${BIN_UNAME} -p
MACH_OS!=	${BIN_UNAME}
MACH_VERS!=	${BIN_UNAME} -r

MACH_VERS_MAJOR=	${MACH_VERS:C/^(.).*/\1/}
# SRC_MACHINES corresponds to the hierarchy in tendra/src/lib/machines.

.if ${MACH_VERS_MAJOR} >= 5
SRC_MACHINES=	${BUILD_OS}/5/${MACH_CPU}
.else
SRC_MACHINES=	${BUILD_OS}/4/${MACH_CPU}
.endif


# Not sure of the best way to get the exec type, suggestions?
MACH_EXEC=	elf

.if ${TMP_CPU} == "i386"
MACH_CPU=	80x86
.elif ${TMP_CPU} == "alpha"
MACH_CPU=	alpha
.endif

.include "config.common.mk"
