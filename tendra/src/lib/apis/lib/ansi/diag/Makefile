# $TenDRA$

.PATH : ${.OBJDIR}/../../../ansi.api

# Set TL_DIAG so we know that we're in the diag directory.
TL_DIAG=	yes

TCCFLAGS+=	-g

# Built in lib/sys
LDADD=  ../../../../sys/sys.j

# Source defines for the api itself
.include "${.CURDIR}/../Makefile.inc"

# Flags for tspec
.include "${.CURDIR}/../../Makefile.inc"
