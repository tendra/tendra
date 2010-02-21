# $Id$

.include "Makefile.inc"


TCCOPTS=	-Yxpg4 -Xs

SRCS+=	archive.c
SRCS+=	compile.c
SRCS+=	environ.c
SRCS+=	execute.c
SRCS+=	filename.c
SRCS+=	flags.c
SRCS+=	list.c
SRCS+=	main.c
SRCS+=	options.c
SRCS+=	stages.c
SRCS+=	startup.c
SRCS+=	utility.c
SRCS+=	table.c

.include <tendra.obj.mk>


PROG=		tcc
WRAPPER=	tcc.sh
EXEC_BIN=	${PREFIX}/lib/tcc/bin

.include <tendra.prog.mk>

