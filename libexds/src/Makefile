# $Id$

.include "Makefile.inc"


CFLAGS+=	-Ishared
CFLAGS+=	-I${BASE_DIR}/include

SRCS+=	bitvec.c
SRCS+=	cstring.c
SRCS+=	dalloc.c
SRCS+=	dstring.c
SRCS+=	error.c
SRCS+=	exception.c
SRCS+=	istream.c
SRCS+=	ostream.c
SRCS+=	syntax.c
SRCS+=	bistream.c
SRCS+=	bostream.c
SRCS+=	cstring-list.c
SRCS+=	nstring-list.c

.include <tendra.obj.mk>

.include <tendra.partial.mk>


LIB=	exds

.include <tendra.lib.mk>

