# $TenDRA$

.PATH : ${.CURDIR} ${.CURDIR}/../../../common

DATA=	K-P5 K-frame K-i386 K-i486 K-noframe \
	Z-p Z-p1 Z-p2 Z-p4 system system+ tcc_prof tdf_ext

INSTALL_ENV=	yes

# This lives in env/, and sucks in the env/common files.
.include "../../../Makefile.inc"

.include "../../../../../../mk/base/tendra.prog.mk"
