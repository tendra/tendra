BASE=/u/g/release/Source
SRC=${BASE}/src/lib/machines/irix/mips/src
SRC2=${BASE}/src/lib/machines/common/src

CC=tcc
TCCOPTS=-Ysystem
REMOVE=rm -f
MOVE=mv
COPY=cp
ECHO=echo
SHELL=/bin/sh

all : dyn_begin.o
	@${ECHO} all done

pre : dyn_begin.o
	@${ECHO} all done

dyn_begin.o : ${SRC}/dyn_begin.c
	${CC} ${TCCOPTS} -c ${SRC}/dyn_begin.c

clean :
	${REMOVE} core

clobber : clean
	${REMOVE} dyn_begin.o
