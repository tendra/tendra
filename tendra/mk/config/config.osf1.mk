# $TenDRA$

UNAME=		/usr/bin/uname

PREFIX=		/usr/local
TMP_DIR=	/tmp
SRC_ENV=	${BUILD_OS}/common/${MACH_CPU}

MACH_CPU!=	${UNAME} -p
MACH_OS!=	${UNAME}
MACH_VERS!=	${UNAME} -r

# Not sure of the best way to get the exec type, suggestions?
MACH_EXEC=	elf

.include "config.common.mk"
