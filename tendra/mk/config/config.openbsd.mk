# $TenDRA$

# Platform dependent commands' locations.
UNAME=		/usr/bin/uname


# Platform settings.
PREFIX?=        /usr/local
MAN_COMPRESS=   yes
MAN_INSTALL=    yes
TMP_DIR=        /tmp


# SRC_ENV corresponds to the hierarchy in tendra/src/lib/env.
SRC_ENV=	${BUILD_OS}/common/${MACH_CPU}

TMP_CPU!=	${UNAME} -m
MACH_OS!=	${UNAME}
MACH_VERS!=	${UNAME} -r


# Not sure of the best way to get the exec type, suggestions?
MACH_EXEC=	elf

.if ${TMP_CPU} == "i386"
MACH_CPU=	80x86
.elif ${TMP_CPU} == "sparc"
MACH_CPU=      sparc
.elif ${TMP_CPU} == "mac68k"
MACH_CPU=      680x0
.endif

# No longer needed
#TCC_OPTS+=	-f${SRC_DIR}/src/lib/machines/${BUILD_OS}/${MACH_CPU}/include/gcc_dependency.h

.include "config.common.mk"
