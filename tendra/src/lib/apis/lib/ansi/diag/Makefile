# $TenDRA$

.PATH : ${.OBJDIR}/../../../ansi.api

TCCFLAGS+=	-g

# Built in lib/sys
LDADD=  ../../../../sys/sys.j

# Source defines for the api itself
.include "${.CURDIR}/../Makefile.inc"

# Flags for tspec
.include "${.CURDIR}/../../Makefile.inc"
