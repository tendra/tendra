# $Id$

SRC2=	${BASE_DIR}/lib/machines/common/src

TCCOPTS=-Ysystem

all: dyn_begin.o dyn_end.o
	@${ECHO} all done

pre:
	@${ECHO} all done

dyn_begin.o: dyn_begin.s
	${CC} ${TCCOPTS} -c dyn_begin.s

dyn_end.o: dyn_end.s
	${CC} ${TCCOPTS} -c dyn_end.s
