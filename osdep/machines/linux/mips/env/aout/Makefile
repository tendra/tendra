# $Id$

.include "Makefile.inc"

.include <tendra.base.mk>


ENVFILE+=	default

ENVFILE+=	tcc_diag
ENVFILE+=	tcc_prof

ENVCOMMON+=	machines/common/env
ENVCOMMON+=	arch/${BLDARCH}/env
ENVCOMMON+=	machines/${OSFAM}/common/env
#ENVCOMMON+=	machines/${OSFAM}/${BLDARCH}/env/common

.include <tendra.env.mk>

