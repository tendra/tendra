# $Id$

.include "Makefile.inc"

.include <tendra.base.mk>
.include <tendra.makedefs.mk>


ENVFILE+=	tcc_prof

ENVCOMMON+=	machines/common/env
#ENVCOMMON+=	machines/${OSFAM}/common/env
ENVCOMMON+=	machines/${OSFAM}/${BLDARCH}/env/common
ENVCOMMON+=	toolchain/mipspro/common
#ENVCOMMON+=	toolchain/mipspro/${BLDARCH}

.include <tendra.env.mk>

