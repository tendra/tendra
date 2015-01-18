# $Id: Makefile 2476 2010-12-25 03:24:17Z kate $

.include "Makefile.inc"


LIBCOPTS+=	-Nsystem:${LIBCPREFIX}/develop/headers/posix
LIBCOPTS+=	-Nsystem_headers:${LIBCPREFIX}/develop/headers
LIBCOPTS+=	-Nsystem_os:${LIBCPREFIX}/develop/headers/os
LIBCOPTS+=	-Nsystem_support:${LIBCPREFIX}/develop/headers/os/support

.for dir in headers os support
HACKOPTS+=	--@D\#pragma@TenDRA@directory@${dir}@use@environment@system\n
.endfor

APIS+=  c89
#APIS+=	c95
#APIS+=	cpp
#APIS+=	system

APIS+=	posix
#APIS+=	posix1
#APIS+=	posix2
#APIS+=	xpg3
#APIS+=	xpg4
#APIS+=	unix95
#APIS+=	svid3

#APIS+=	gcc
#APIS+=	bsd_extn

.include <tendra.api.mk>

