# $Id$

.include "Makefile.inc"


LIBCOPTS+=	-Nsystem:/usr/include

# for Ubuntu and other Debian-like systems
.if exists(/usr/include/i386-linux-gnu)
LIBCOPTS+=	-Nsystem_arch:/usr/include/i386-linux-gnu
.endif

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

