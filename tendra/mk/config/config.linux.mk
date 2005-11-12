# $TenDRA$

# Platform settings.
PREFIX?=        /usr/local
MAN_COMPRESS=   yes
MAN_INSTALL=    yes
TMP_DIR=        /tmp


# SRC_ENV corresponds to the hierarchy in tendra/src/lib/env.
SRC_ENV=	${BUILD_OS}/${MACH_EXEC}/${MACH_CPU}
# SRC_MACHINES corresponds to the hierarchy in tendra/src/lib/machines.
SRC_MACHINES=	${BUILD_OS}/${MACH_CPU}

TMP_CPU!=	${BIN_UNAME} -m
MACH_OS!=	${BIN_UNAME}
MACH_VERS!=	${BIN_UNAME} -r


# Not sure of the best way to get the exec type, suggestions?
MACH_EXEC=	elf

.if ${TMP_CPU} == "i386" || ${TMP_CPU} == "i486" || ${TMP_CPU} == "i586" || ${TMP_CPU} == "i686"
MACH_CPU=	80x86
.else
MACH_CPU=	${TMP_CPU}
.endif

.include "config.common.mk"
