# $TenDRA$

.PATH : ${.OBJDIR}/../../posix1.api

TCCFLAGS+=	-f${OBJ_PREFIX}/lib/machines/${BUILD_OS}/${MACH_CPU}/startup/posix1.h

TL=	posix1.tl

SRCS=	limits.c locale.c ssize_t.c unistd.c

.include "../../../../../mk/base/tendra.prog.mk"

