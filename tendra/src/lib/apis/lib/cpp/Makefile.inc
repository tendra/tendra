# $TenDRA$

TCCFLAGS+=	-f${OBJ_PREFIX}/lib/machines/${SRC_MACHINES}/startup/cpp.h

.PATH : ${.OBJDIR}/../../cpp.api

TL=	cpp.tl

SRCS=	cstdlib.c

# This is a very crappy way to handle this.
LDADD?=  ../../../libcpp/tokens/basic.j ../../../libcpp/tokens/ptr_func.j \
        ../../../libcpp/tokens/ptr_mem.j ../../../libcpp/tokens/throw.j \
        ../../../libcpp/tokens/vtable.j

.include "../../../../../mk/base/tendra.prog.mk"

