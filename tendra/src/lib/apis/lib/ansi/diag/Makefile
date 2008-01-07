# $TenDRA$

.PATH : ${.OBJDIR}/../../../ansi.api

TCCFLAGS+=	-g

# Set TL_DIAG so we know that we're in the diag directory.
TL_DIAG=	yes

# Built in lib/sys
LDADD=  ../../../../sys/sys.j

# Source defines for the api itself
.include "${.CURDIR}/../Makefile.inc"
