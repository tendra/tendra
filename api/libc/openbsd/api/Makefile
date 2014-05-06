# $Id$

.include "Makefile.inc"


JOPTS+=	-I/usr/include

APIS+=  c89
APIS+=  c89-fs
APIS+=	c90
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

#APIS+= sus/xsh2

APIS+= xns5-socket

# This OS makes no attempt to provide conformance for these APIs
#APIS+= acse-xap
#APIS+= dtp-xa
#APIS+= xns5-ar

.include <tendra.api.mk>

