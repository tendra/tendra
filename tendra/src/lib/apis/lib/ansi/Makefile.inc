# $TenDRA$

.include "../Makefile.inc"

# Generated API Makefile
.include "${API_GEN}/Makefile"

# Built in lib/sys
LDADD?=	../../../sys/sys.j

.include "../../../../../mk/base/tendra.prog.mk"
