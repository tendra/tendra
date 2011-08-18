# $Id$

.include <tendra.situ.mk>

SRC2=	${BASE_DIR}/lib/machines/common/src

#TCCOPTS=	-Ysystem
CCOPTS=		-I${SRC2}

SRCS+=	main.c

all:: dyninit TDFpower.o
	./${OBJ_SDIR}/dyninit TDFpower.o

.include "Makefile.inc"


PROG=	dyninit

.include <tendra.prog.mk>

