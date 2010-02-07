# $Id$

.include "Makefile.inc"


TCCOPTS=	-Yxpg4 -Xs
SRCS=		archive.c compile.c environ.c execute.c filename.c flags.c\
		list.c main.c options.c stages.c startup.c utility.c table.c

.include <tendra.obj.mk>


PROG=		${.CURDIR:T}
WRAPPER=	${.CURDIR:T}.sh

.include <tendra.prog.mk>

