# $TenDRA$

# Platform dependent commands' locations.
UNAME=		/bin/uname


# Platform settings.
PREFIX?=        /usr/local
MAN_COMPRESS=   yes
MAN_INSTALL=    yes
TMP_DIR=        /tmp


# SRC_ENV corresponds to the hierarchy in tendra/src/lib/env.
SRC_ENV=	${BUILD_OS}/${MACH_EXEC}/${MACH_CPU}

TMP_CPU!=	${UNAME} -m
MACH_OS!=	${UNAME}
MACH_VERS!=	${UNAME} -r


# Not sure of the best way to get the exec type, suggestions?
MACH_EXEC=	elf

.if ${TMP_CPU} == "i386" || ${TMP_CPU} == "i486" || ${TMP_CPU} == "i586" || ${TMP_CPU} == "i686"
MACH_CPU=	80x86
.else
MACH_CPU=	${TMP_CPU}
.endif

.include "config.common.mk"
