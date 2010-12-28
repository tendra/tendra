# $Id$

SRC2=	${BASE_DIR}/src/lib/machines/common/src

#TCCOPTS=-Ysystem

# Environments are not yet installed, so we use them in-situ.
TCCOPTS+=	--SED${OBJ_DIR}/env --CFE

all : dyn_begin.o
	@${ECHO} all done

.include "Makefile.inc"
