# $TenDRA$

TCCFLAGS+=	-f${OBJ_PREFIX}/lib/machines/${BUILD_OS}/${MACH_CPU}/startup/bsd_extn.h

.PATH : ${.OBJDIR}/../../bsd_extn.api

TL=	bsd_extn.tl

SRCS=	alloca.c errno.c in.c inet.c netdb.c param.c resource.c \
	select.c socket.c strings.c syslog.c timeval.c uio.c

.include "../../../../../mk/base/tendra.prog.mk"

