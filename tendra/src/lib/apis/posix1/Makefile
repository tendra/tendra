# $TenDRA$

TCCFLAGS=	-f${OBJ_PREFIX}/lib/machines/${BUILD_OS}/${MACH_CPU}/startup/posix1.h

TL=	posix1.tl

SRCS=	limits.c locale.c ssize_t.c unistd.c

.include "../Makefile.inc"

.include "${.CURDIR}/../../../../mk/base/tendra.prog.mk"
