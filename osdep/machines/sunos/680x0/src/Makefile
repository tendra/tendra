# $Id$

SRC2=	${BASE_DIR}/lib/machines/common/src

#TCCOPTS=	-Ysystem
#CCOPTS=

SRCS+=	dyninit.c

# Environments are not yet installed, so we use them in-situ.
TCCOPTS+=	--SED${OBJ_DIR}/env --CFE

.include "Makefile.inc"


PROG=	dyninit

.include <tendra.prog.mk>

