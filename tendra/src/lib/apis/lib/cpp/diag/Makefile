# $TenDRA$

.PATH : ${.OBJDIR}/../../../cpp.api

TCCFLAGS+=	-g

# Source defines for the api itself
.include "${.CURDIR}/../Makefile.inc"

# Flags for tspec
.include "${.CURDIR}/../../Makefile.inc"

# This is a very crappy way to handle this.
# These files are built in lib/libcpp/tokens
LDADD=  ../../../../libcpp/tokens/basic.j ../../../../libcpp/tokens/ptr_func.j \
	../../../../libcpp/tokens/ptr_mem.j ../../../../libcpp/tokens/throw.j \
	../../../../libcpp/tokens/vtable.j
