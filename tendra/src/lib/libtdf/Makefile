# $Id$

LIB=	tdf
SRCS=	INT64a.o version.o

TPLOPTS=	-I${.CURDIR}

INT64a.o: INT64a.j INT64b.j abstract.j
	${TCC} -c -o ${.TARGET} INT64a.j INT64b.j abstract.j -jtarget_tok -M

CLEAN_EXTRA+=	INT64a.j INT64b.j abstract.j

.include "Makefile.inc"
