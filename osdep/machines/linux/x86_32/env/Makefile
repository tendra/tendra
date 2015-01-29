# $Id$

.include "Makefile.inc"

.include <tendra.base.mk>
.include <tendra.makedefs.mk>


ENVFILE+=	default

ENVFILE+=	K-aout

ENVFILE+=	tdf_ext

ENVCOMMON+=	machines/common/env
ENVCOMMON+=	arch/${BLDARCH}
ENVCOMMON+=	machines/${OSFAM}/common/env
#ENVCOMMON+= machines/${OSFAM}/${BLDARCH}/env
#ENVCOMMON+=	machines/${LIBCFAM}/common/env
ENVCOMMON+= machines/${LIBCFAM}/${BLDARCH}/env
ENVCOMMON+=	toolchain/gnu/common
ENVCOMMON+=	toolchain/gnu/${BLDARCH}

.include <tendra.env.mk>

