# $TenDRA$

# Platform dependent commands' locations.
UNAME=		/usr/bin/uname


# Platform settings.
PREFIX?=	/usr/local
MAN_COMPRESS=	yes
MAN_INSTALL=	yes
TMP_DIR=	/tmp


# SRC_ENV corresponds to the hierarchy in tendra/src/lib/env.
SRC_ENV=	${BUILD_OS}/common/${MACH_CPU}
# SRC_MACHINES corresponds to the hierarchy in tendra/src/lib/machines.
SRC_MACHINES=	${BUILD_OS}/${MACH_CPU}

TMP_CPU!=	${UNAME} -p
MACH_OS!=	${UNAME}
MACH_VERS!=	${UNAME} -r


# Not sure of the best way to get the exec type, suggestions?
MACH_EXEC=	elf

.if ${TMP_CPU} == "powerpc"
MACH_CPU=	power
.endif

.include "config.common.mk"
