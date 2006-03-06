BASE=/u/g/release/Source
SRC=${BASE}/src/lib/machines/minix/80x86/src
SRC2=${BASE}/src/lib/machines/common/src

CC=tcc
AS=/usr/lib/i386/as -
TCCOPTS=-Ysystem
REMOVE=rm -f
MOVE=mv
COPY=cp
ECHO=echo
SHELL=/bin/sh

all : crtso.o cpprtso.o end
	@${ECHO} all done

pre : dyninit
	@${ECHO} all done

dyninit : ${SRC}/dyninit.c ${SRC2}/ossg.h
	${CC} ${TCCOPTS} -I${SRC2} -o dyninit.new ${SRC}/dyninit.c
	${REMOVE} dyninit
	${MOVE} dyninit.new dyninit

crtso.o : ${SRC}/crtso.s
	${AS} -o crtso.new ${SRC}/crtso.s
	${REMOVE} crtso.o
	${MOVE} crtso.new crtso.o

cpprtso.o : ${SRC}/cpprtso.s
	${AS} -o cpprtso.new ${SRC}/cpprtso.s
	${REMOVE} cpprtso.o
	${MOVE} cpprtso.new cpprtso.o

end :
	mkdir -p objs
	cd objs && ${MAKE} -f ${SRC}/end.mak
	rmdir objs

clean :
	${REMOVE} core

clobber : clean
	${REMOVE} dyninit crtso.o cpprtso.o end.a
