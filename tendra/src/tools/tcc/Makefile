# $Id$

# Standard variables

CC?=		tcc
TCCOPTS=	-Yxpg4 -Xs
CCOPTS=		${TCCOPTS} -I${SRC}
LIBS=

# Dependencies and construction rules

PROG=		tcc1

SRCS=		archive.c compile.c environ.c execute.c filename.c flags.c\
		list.c main.c options.c stages.c startup.c utility.c

.include "../Makefile.inc"
