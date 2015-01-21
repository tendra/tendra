# $Id: Makefile 2591 2011-08-13 22:12:23Z kate $

.include "Makefile.inc"

.include <tendra.base.mk>


ENVFILE+=	default

ENVFILE+=	tcc_diag

ENVCOMMON+=	machines/common/env
ENVCOMMON+=	machines/${OSFAM}/common/env
ENVCOMMON+=	machines/${OSFAM}/mips/env/common
ENVCOMMON+=	toolchain/ultrix/common
#ENVCOMMON+=	toolchain/ultrix/${BLDARCH}

.include <tendra.env.mk>

