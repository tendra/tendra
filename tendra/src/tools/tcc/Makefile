# $Id$

# Standard variables

WARNS?=		0

TCCOPTS=	-Yxpg4 -Xs
CCOPTS=		${TCCOPTS} -I${BASE_DIR}/${INCLUDE} -I${.CURDIR}
LIBS=

# Dependencies and construction rules

PROG=		${.CURDIR:T}
MAN=		tcc.1 tccenv.5
WRAPPER=	tcc.sh

SRCS=		archive.c compile.c environ.c execute.c filename.c flags.c\
		list.c main.c options.c stages.c startup.c utility.c

.include "../Makefile.inc"
