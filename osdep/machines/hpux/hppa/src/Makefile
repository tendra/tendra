# $Id$

.include <tendra.compiler.mk>

SRC2=	${BASE_DIR}/lib/machines/common/src

#TCCOPTS=-Ysystem

all:: dyn_begin.o dyn_end.o
	@${ECHO} all done

pre:
	@${ECHO} all done

dyn_begin.o: dyn_begin.s
	${TCC} ${TCCOPTS} -c dyn_begin.s

dyn_end.o: dyn_end.s
	${TCC} ${TCCOPTS} -c dyn_end.s

.include "Makefile.inc"
