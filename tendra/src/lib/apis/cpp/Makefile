# $TenDRA$

TCCFLAGS=	-f${OBJ_PREFIX}/lib/machines/${BUILD_OS}/${MACH_CPU}/startup/cpp.h

TL=	cpp.tl

SRCS=	basic.c cstdlib.c ptr_func.c ptr_mem.c throw.c vtable.c

.include "../Makefile.inc"

.include "${.CURDIR}/../../../../mk/base/tendra.prog.mk"
