# $Id$

.include "Makefile.inc"


# TODO: ugly and confusing
ENVCOMMON+= ${OBJ_DIR:C|^${BASE_DIR}/||}/share/TenDRA/env
LISTENVS = ls -1

ENVFILE+=	c89
ENVFILE+=	c89-fs
ENVFILE+=	c90
ENVFILE+=	ansi
ENVFILE+=	iso

ENVFILE+=	cose
ENVFILE+=	xsh4
ENVFILE+=	xpg3
ENVFILE+=	xpg4

ENVFILE+=	posix
ENVFILE+=	posix1
ENVFILE+=	posix2

ENVFILE+=	strict_posix
ENVFILE+=	strict_svid3
ENVFILE+=	strict_xpg3
ENVFILE+=	strict_mot_1_2

ENVFILE+=	gcc
ENVFILE+=	alloca
ENVFILE+=	motif_private

ENVFILE+=	x5_proto
ENVFILE+=	x5_private

PREFIX_ENV:=	${PREFIX_TSPEC}/TenDRA/env

.include <tendra.env.mk>

