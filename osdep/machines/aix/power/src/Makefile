# $Id$

SRC2=	${BASE_DIR}/lib/machines/common/src

#TCCOPTS=	-Ysystem
CCOPTS=		-I${SRC2}

# Environments are not yet installed, so we use them in-situ.
TCCOPTS+=	--SED${OBJ_DIR}/env --CFE

SRCS+=	dyninit.c

all:: dyninit TDFpower.o
	./${OBJ_SDIR}/dyninit TDFpower.o

.include "Makefile.inc"


PROG=	dyninit

.include <tendra.prog.mk>

