# $TenDRA$
#
# There never was a ppc601 installer, it's the same as the power installer.
# this extra target was created because there are difference in lib/env, 
# lib/machines for ppc601

SRCDIRS+=       power/aix

PROG=	trans

# installers/power/aix
SRCS=	powertrans.c

# installers/power
.include "../../power/Makefile.inc"

# installers/
.include "${.CURDIR}/../../Makefile.inc"

.include "${.CURDIR}/../../../../mk/base/tendra.prog.mk"
