BASE=/u/g/release/Source
SRC=${BASE}/src/lib/machines/sunos/680x0/src
SRC2=${BASE}/src/lib/machines/common/src

CC=tcc
TCCOPTS=-Ysystem
REMOVE=rm -f
MOVE=mv
COPY=cp
ECHO=echo
SHELL=/bin/sh

all : dyninit
	@${ECHO} all done

pre : dyninit
	@${ECHO} all done

dyninit : ${SRC}/dyninit.c ${SRC2}/ossg.h
	${CC} ${TCCOPTS} -I${SRC2} -o dyninit.new ${SRC}/dyninit.c
	${REMOVE} dyninit
	${MOVE} dyninit.new dyninit

clean :
	${REMOVE} core

clobber : clean
	${REMOVE} dyninit
