# $Id$

.include "Makefile.inc"

.include <tendra.base.mk>
.include <tendra.makedefs.mk>


ENVFILE+=	default

ENVFILE+=	K-aout

ENVFILE+=	system
ENVFILE+=	system+
ENVFILE+=	tcc_prof
ENVFILE+=	tdf_ext

ENVCOMMON+=	machines/common/env
ENVCOMMON+=	arch/${BLDARCH}/env
ENVCOMMON+=	machines/${OSFAM}/common/env
#ENVCOMMON+= machines/${OSFAM}/${BLDARCH}/env/common

.include <tendra.env.mk>

