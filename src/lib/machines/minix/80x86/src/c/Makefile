BASE=/u/g/release/Source
SRC=${BASE}/src/lib/machines/minix/80x86/src/c

CC=tcc
AS=/usr/lib/i386/as
TCCOPTS=-Ysystem
REMOVE=rm -f
MOVE=mv
COPY=cp
ECHO=echo
SHELL=/bin/sh

all :
	${MAKE} -f ${SRC}/ansi.mak    NAME=${NAME}
	${MAKE} -f ${SRC}/ip.mak      NAME=${NAME}
	${MAKE} -f ${SRC}/math.mak    NAME=${NAME} SRC1=${SRC}
	${MAKE} -f ${SRC}/other.mak   NAME=${NAME}
	${MAKE} -f ${SRC}/posix.mak   NAME=${NAME} SRC1=${SRC}
	${MAKE} -f ${SRC}/stdio.mak   NAME=${NAME}
	${MAKE} -f ${SRC}/syscall.mak NAME=${NAME}
	${MAKE} -f ${SRC}/syslib.mak  NAME=${NAME}
	${MAKE} -f ${SRC}/misc.mak    NAME=${NAME}
	${MAKE} -f ${SRC}/rts.mak     NAME=${NAME} SRC1=${SRC}
	${MAKE} -f ${SRC}/string.mak  NAME=${NAME}
	@${ECHO} all done

clean :
	${REMOVE} core

clobber : clean
	${REMOVE} ${NAME}
