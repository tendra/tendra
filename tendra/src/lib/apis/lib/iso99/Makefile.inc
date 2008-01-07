# $TenDRA$

TCCFLAGS+=	-Yc99

.include "../Makefile.inc"

# Generated API Makefile
.include "${API_GEN}/Makefile"

.include "../../../../../mk/base/tendra.prog.mk"
