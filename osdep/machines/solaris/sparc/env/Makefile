# $Id$

.include "Makefile.inc"

.include <tendra.base.mk>
.include <tendra.makedefs.mk>


ENVFILE=	default

ENVFILE+=	Goption

ENVFILE+=	K-pic

ENVCOMMON+=	machines/common/env
ENVCOMMON+=	arch/${BLDARCH}
ENVCOMMON+=	machines/${OSFAM}/common/env
ENVCOMMON+=	toolchain/sun/common
ENVCOMMON+=	toolchain/sun/${BLDARCH}

.include <tendra.env.mk>

