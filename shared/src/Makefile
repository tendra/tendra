# $Id$

.include "Makefile.inc"


SRCS+=	error.c
SRCS+=	fmt.c
SRCS+=	xalloc.c
SRCS+=	string.c
SRCS+=	getopt.c

CCOPTS+=	-DRELEASE='"${RELEASE}"'

TCCOPTS.error.c+=	-Yposix

.include <tendra.obj.mk>

.include <tendra.partial.mk>

