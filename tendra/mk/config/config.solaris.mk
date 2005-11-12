# $TenDRA$

# Platform settings.
PREFIX?=	/usr/local
MAN_COMPRESS=	yes
MAN_INSTALL=	yes
TMP_DIR=	/tmp


# SRC_ENV corresponds to the hierarchy in tendra/src/lib/env.
SRC_ENV=	${BUILD_OS}/common/${MACH_CPU}
# SRC_MACHINES corresponds to the hierarchy in tendra/src/lib/machines.
SRC_MACHINES=	${BUILD_OS}/${MACH_CPU}

MACH_CPU!=	${BIN_UNAME} -p
MACH_OS=	Solaris
MACH_VERS!=	${BIN_UNAME} -r


# Not sure of the best way to get the exec type, suggestions?
MACH_EXEC=	elf

.include "config.common.mk"
