BASE=/u/g/release/Source
SRC=${BASE}/src/lib/machines/common/src

CC=tcc
TCCOPTS=-Ysystem
REMOVE=rm -f
MOVE=mv
COPY=cp
ECHO=echo
SHELL=/bin/sh

all : crtp_n.o
	@${ECHO} all done

crtp_n.o : ${SRC}/crtp_n.pl
	${CC} -Ypl_tdf -c ${SRC}/crtp_n.pl

clean :
	${REMOVE} core

clobber : clean
	${REMOVE} crtp_n.o
