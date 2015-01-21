# $Id$

.include "Makefile.inc"

.include <tendra.base.mk>
.include <tendra.makedefs.mk>


ENVFILE+=	default

ENVCOMMON+=	machines/common/env
ENVCOMMON+=	arch/${BLDARCH}
ENVCOMMON+=	machines/${OSFAM}/common/env
ENVCOMMON+=	toolchain/gnu/common
ENVCOMMON+=	toolchain/gnu/${BLDARCH}

.include <tendra.env.mk>

