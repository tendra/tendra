BASE=/u/g/release/Source
SRC=${BASE}/src/lib/cpp/tokens
SRC2=${BASE}/src/lib/cpp/src

TCC=tcc
TCCOPTS=-Yc++ -I${SRC2}
TNC=tnc

REMOVE=rm -f
ECHO=echo
SHELL=/bin/sh

SYS_FILES=basic.j ptr_func.j ptr_mem.j throw.j vtable.j

all : ${SYS_FILES}
	@${ECHO} all done

basic.j : ${SRC}/basic.cc ${SRC2}/basic.h ${SRC2}/implement.h
	${TCC} ${TCCOPTS} -Fj -o basic.j ${SRC}/basic.cc

ptr_func.j : ${SRC}/ptr_func.p
	${TNC} ${SRC}/ptr_func.p ptr_func.j

ptr_mem.j : ${SRC}/ptr_mem.p
	${TNC} ${SRC}/ptr_mem.p ptr_mem.j

throw.j : ${SRC}/throw.cc  ${SRC2}/implement.h ${SRC2}/longjump.h\
 ${SRC2}/offset.h ${SRC2}/throw.h
	${TCC} ${TCCOPTS} -Fj -o throw.j ${SRC}/throw.cc

vtable.j : ${SRC}/vtable.p
	${TNC} ${SRC}/vtable.p vtable.j

clean :
	${REMOVE} core

clobber : clean
	${REMOVE} ${SYS_FILES}
