# $Id: Makefile 2476 2010-12-25 03:24:17Z kate $

.include "Makefile.inc"


LIBCOPTS+=	-Nsystem_posix:/boot/develop/headers/posix
LIBCOPTS+=	-Nsystem_headers:/boot/develop/headers
LIBCOPTS+=	-Nsystem_os:/boot/develop/headers/os
LIBCOPTS+=	-Nsystem_support:/boot/develop/headers/os/support

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

