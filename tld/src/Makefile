# $Id$

.include "Makefile.inc"


PARTS+= src/shared
PARTS+= src/exds
PARTS+=	src/adt
PARTS+=	src/frontend

.include <tendra.partial.mk>


TCCOPTS=	-Xs

TCCOPTS.file-name.c+=	-Yposix

CCOPTS+=	-I .

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

