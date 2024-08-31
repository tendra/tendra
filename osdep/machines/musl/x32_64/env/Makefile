# $Id$

.include "Makefile.inc"

.include <tendra.base.mk>
.include <tendra.makedefs.mk>

ENVFILE+=	default

ENVFILE+=	tcc_prof

.include <tendra.env.mk>

.BEGIN:
	@cp -r ${BASE_DIR}/machines/musl/common/${USE_LIBC}-template/env ${BASE_DIR}/machines/musl/${BLDARCH}
