# $TenDRA$

UNAME=		/usr/bin/uname

PREFIX=		/usr/local
TMP_DIR=	/tmp

TMP_CPU!=	${UNAME} -p
MACH_OS!=	${UNAME}
MACH_VERS!=	${UNAME} -r

# Not sure of the best way to get the exec type, suggestions?
MACH_EXEC=	elf

.if ${TMP_CPU} == "powerpc"
MACH_CPU=	power
.endif

.include "config.common.mk"
