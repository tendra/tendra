# $TenDRA$

TCCFLAGS+=	-f${OBJ_PREFIX}/lib/machines/${BUILD_OS}/${MACH_CPU}/startup/gcc.h

.PATH : ${.OBJDIR}/../../gcc.api

TL=	gcc.tl

SRCS=	param.c resource.c tdf_alloca.c timeval.c

.include "../../../../../mk/base/tendra.prog.mk"

