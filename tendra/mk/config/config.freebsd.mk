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

TMP_CPU!=	${UNAME} -p
MACH_OS!=	${UNAME}
MACH_VERS!=	${UNAME} -r

# SRC_MACHINES corresponds to the hierarchy in tendra/src/lib/machines.
.if ${MACH_VERS:R} == "5"
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


# No longer needed
#TCC_OPTS+=	-f${SRC_DIR}/src/lib/machines/${BUILD_OS}/${MACH_CPU}/include/gcc_dependency.h

.include "config.common.mk"
