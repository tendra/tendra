# $Id$

.include "Makefile.inc"

.include <tendra.base.mk>


ENVFILE+=	default

ENVFILE+=	posix_lib
ENVFILE+=	static

ENVCOMMON+=	machines/common/env
ENVCOMMON+=	machines/${OSFAM}/common/env
ENVCOMMON+=	toolchain/osf1/common
#ENVCOMMON+=	toolchain/osf1/${BLDARCH}

.include <tendra.env.mk>

