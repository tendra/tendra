# $TenDRA$

.PATH : ${.OBJDIR}/../../posix2.api

TCCFLAGS+=	-f${OBJ_PREFIX}/lib/machines/${BUILD_OS}/${MACH_CPU}/startup/posix2.h

TL=	posix2.tl

SRCS=	fnmatch.c glob.c limits.c regex.c unistd.c wordexp.c

.include "../../../../../mk/base/tendra.prog.mk"

