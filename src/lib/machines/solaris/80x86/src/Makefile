BASE=/u/g/release/Source
SRC=${BASE}/src/lib/machines/solaris/80x86/src
SRC2=${BASE}/src/lib/machines/common/src

CC=tcc
TCC=tcc
TNC=tnc
TCCOPTS=-Ysystem
REMOVE=rm -f
MOVE=mv
COPY=cp
ECHO=echo
SHELL=/bin/sh

all : crt1.o crti.o crtn.o dwarf.o
	@${ECHO} all done

pre :
	@${ECHO} all done

crt1.o : ${SRC}/crt1.s
	${CC} ${TCCOPTS} -c ${SRC}/crt1.s

crti.o : ${SRC}/crti.s
	${CC} ${TCCOPTS} -c ${SRC}/crti.s

crtn.o : ${SRC}/crtn.s
	${CC} ${TCCOPTS} -c ${SRC}/crtn.s

dwarf.o : ${SRC}/dwarf.t
	${TCC} -Wt,-T -c ${SRC}/dwarf.t

${SRC}/dwarf.t : ${SRC}/dwarf.p
	${TNC} ${SRC}/dwarf.p ${SRC}/dwarf.t

clean :
	${REMOVE} core

clobber : clean
	${REMOVE} crt1.o crti.o crtn.o dwarf.o
