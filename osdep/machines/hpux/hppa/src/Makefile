# $Id$

SRC2=	${BASE_DIR}/lib/machines/common/src

#TCCOPTS=-Ysystem

# Environments are not yet installed, so we use them in-situ.
TCCOPTS+=	--SED${OBJ_DIR}/env --CFE

all:: dyn_begin.o dyn_end.o
	@${ECHO} all done

pre:
	@${ECHO} all done

dyn_begin.o: dyn_begin.s
	${CC} ${TCCOPTS} -c dyn_begin.s

dyn_end.o: dyn_end.s
	${CC} ${TCCOPTS} -c dyn_end.s

.include "Makefile.inc"
