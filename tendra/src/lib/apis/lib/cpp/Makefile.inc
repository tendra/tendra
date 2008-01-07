# $TenDRA$

.include "../Makefile.inc"

# Generated API Makefile
.include "${API_GEN}/Makefile"

# Override
SRCS=	cstdlib.c

# This is a very crappy way to handle this.
LDADD?=  ../../../libcpp/tokens/basic.j ../../../libcpp/tokens/ptr_func.j \
        ../../../libcpp/tokens/ptr_mem.j ../../../libcpp/tokens/throw.j \
        ../../../libcpp/tokens/vtable.j

.include "../../../../../mk/base/tendra.prog.mk"
