BASE=/u/g/release/Source
SRC=${BASE}/src/lib/machines/hpux/hppa/src
SRC2=${BASE}/src/lib/machines/common/src

CC=tcc
TCCOPTS=-Ysystem
REMOVE=rm -f
MOVE=mv
COPY=cp
ECHO=echo
SHELL=/bin/sh

all : dyn_begin.o dyn_end.o
	@${ECHO} all done

pre :
	@${ECHO} all done

dyn_begin.o : ${SRC}/dyn_begin.s
	${CC} ${TCCOPTS} -c ${SRC}/dyn_begin.s

dyn_end.o : ${SRC}/dyn_end.s
	${CC} ${TCCOPTS} -c ${SRC}/dyn_end.s

clean :
	${REMOVE} core

clobber : clean
	${REMOVE} dyn_begin.o dyn_end.o
