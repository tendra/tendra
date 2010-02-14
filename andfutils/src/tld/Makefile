# $Id$

.include "Makefile.inc"


PARTS+= src/shared/error
PARTS+= src/shared/xalloc
PARTS+=	src/tld/adt
PARTS+=	src/tld/frontend

.include <tendra.partial.mk>


CCOPTS+=	-I../shared
CCOPTS+=	-I.

SRCS+=	arg-parse.c
SRCS+=	debug.c
SRCS+=	file-name.c
SRCS+=	fmt.c
SRCS+=	main.c
SRCS+=	rename-file.c
SRCS+=	syntax.c
SRCS+=	tdf.c

.include <tendra.obj.mk>


PROG=	${.CURDIR:T}
LIBS=	-lexds

.include <tendra.prog.mk>

