# $TenDRA$

TCCFLAGS=	-f${OBJ_PREFIX}/lib/machines/${BUILD_OS}/${MACH_CPU}/startup/gcc.h

TL=	gcc.tl

SRCS=	param.c resource.c tdf_alloca.c timeval.c

.include "../Makefile.inc"

.include "${.CURDIR}/../../../../mk/base/tendra.prog.mk"
