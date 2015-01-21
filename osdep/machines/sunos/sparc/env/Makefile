# $Id$

.include "Makefile.inc"

.include <tendra.base.mk>
.include <tendra.makedefs.mk>


ENVFILE+=	default

ENVFILE+=	K-pic

ENVFILE+=	tcc_diag
ENVFILE+=	tcc_prof
ENVFILE+=	tdf_ext

ENVCOMMON+=	machines/common/env
ENVCOMMON+=	arch/${BLDARCH}/env
ENVCOMMON+=	machines/${OSFAM}/common/env
ENVCOMMON+=	toolchain/sun/common
ENVCOMMON+=	toolchain/sun/${BLDARCH}

.include <tendra.env.mk>

