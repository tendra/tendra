# $TenDRA$

.PATH : ${.OBJDIR}/../../../posix1.api

TCCFLAGS+=	-g

# Set TL_DIAG so we know that we're in the diag directory.
TL_DIAG=	yes

# Source defines for the api itself
.include "${.CURDIR}/../Makefile.inc"

# Flags for tspec
.include "${.CURDIR}/../../Makefile.inc"
