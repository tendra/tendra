# $Id$

.include "Makefile.inc"


PART_CFLAGS+=	-I${.CURDIR}/shared

PARTS+= src/shared/error
PARTS+= src/shared/xalloc
PARTS+= src/exds
PARTS+=	src/adt
PARTS+=	src/frontend

.include <tendra.partial.mk>


CCOPTS+=	-Ishared
CCOPTS+=	-I.

CFLAGS+=	-I${BASE_DIR}/include

SRCS+=	arg-parse.c
SRCS+=	debug.c
SRCS+=	file-name.c
SRCS+=	fmt.c
SRCS+=	main.c
SRCS+=	rename-file.c
SRCS+=	tdf.c

.include <tendra.obj.mk>


PROG=	tld

.include <tendra.prog.mk>

