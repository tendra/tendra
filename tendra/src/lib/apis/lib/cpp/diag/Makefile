# $TenDRA$

.PATH : ${.OBJDIR}/../../../cpp.api

TCCFLAGS+=	-g

# Set TL_DIAG so we know that we're in the diag directory.
TL_DIAG=	yes

# This is a very crappy way to handle this.
# These files are built in lib/libcpp/tokens
LDADD=  ../../../../libcpp/tokens/basic.j ../../../../libcpp/tokens/ptr_func.j \
	../../../../libcpp/tokens/ptr_mem.j ../../../../libcpp/tokens/throw.j \
	../../../../libcpp/tokens/vtable.j

# Source defines for the api itself
.include "${.CURDIR}/../Makefile.inc"
