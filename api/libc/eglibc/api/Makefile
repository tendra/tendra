# $Id$

.include "Makefile.inc"


JOPTS+=	-I/usr/include

# for Ubuntu and other Debian-like systems
.if exists(/usr/include/i386-linux-gnu)
JOPTS+=	-I/usr/include/i386-linux-gnu
.endif

APIS+=  ansi
#APIS+=	iso
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

