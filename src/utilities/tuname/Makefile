# Standard directories and files
BASE=/u/g/release/Source
UTIL=${BASE}/src/utilities
SRC=${UTIL}/tuname
SRCX=${UTIL}/shared

CC=tcc
TCCOPTS=-Ysystem
CCOPTS=${TCCOPTS} -I${SRCX}
LIBS=

REMOVE=rm -f
MOVE=mv
COPY=cp
ECHO=echo
SHELL=/bin/sh

# Dependencies and construction rules

NAME=tuname

${NAME} : ${SRC}/tuname.c ${SRCX}/ossg.h
	${CC} ${CCOPTS} -o ${NAME} ${SRC}/tuname.c ${LIBS}

all : ${NAME}
	@${ECHO} all done

extra :
	@${ECHO} done

clean :
	${REMOVE} core

clobber : clean
	${REMOVE} ${NAME}
