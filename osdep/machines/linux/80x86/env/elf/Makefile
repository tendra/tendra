# $Id$

.include "Makefile.inc"


ENVFILE+=	default

ENVFILE+=	K-aout

ENVFILE+=	Z-p
ENVFILE+=	Z-p1
ENVFILE+=	Z-p2
ENVFILE+=	Z-p4

ENVFILE+=	system
ENVFILE+=	system+
ENVFILE+=	tcc_prof
ENVFILE+=	tdf_ext

ENVCOMMON+=	machines/common/env
ENVCOMMON+=	machines/common/arch/${BLDARCH}/env
ENVCOMMON+=	machines/${OSFAM}/common/env
#ENVCOMMON+= machines/${OSFAM}/${BLDARCH}/env/common

.include <tendra.env.mk>

