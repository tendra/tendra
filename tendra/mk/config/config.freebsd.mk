# $TenDRA$

# Platform dependent commands' locations.
UNAME=		/usr/bin/uname

# SRC_ENV corresponds to the hierarchy in tendra/src/lib/env.
PREFIX?=	/usr/local
TMP_DIR=	/tmp
SRC_ENV=	${BUILD_OS}/common/${MACH_CPU}

TMP_CPU!=	${UNAME} -p
MACH_OS!=	${UNAME}
MACH_VERS!=	${UNAME} -r

# Not sure of the best way to get the exec type, suggestions?
MACH_EXEC=	elf

.if ${TMP_CPU} == "i386"
MACH_CPU=	80x86
.endif

TCC_OPTS+=	-f${SRC_DIR}/src/lib/machines/${BUILD_OS}/${MACH_CPU}/include/gcc_dependency.h

.include "config.common.mk"
