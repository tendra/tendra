# $Id$

SRC=${BASE}/src/lib/cpp/src

TCCOPTS=-Yc++ -I${SRC}

SYS_FILES=basic.j ptr_func.j ptr_mem.j throw.j vtable.j

all: ${SYS_FILES}
	@${ECHO} all done

basic.j: basic.cc ${SRC}/basic.h ${SRC}/implement.h
	${TCC} ${TCCOPTS} -Fj -o basic.j basic.cc

ptr_func.j: ptr_func.p
	${TNC} ptr_func.p ptr_func.j

ptr_mem.j: ptr_mem.p
	${TNC} ptr_mem.p ptr_mem.j

throw.j: throw.cc  ${SRC}/implement.h ${SRC}/longjump.h\
 ${SRC}/offset.h ${SRC}/throw.h
	${TCC} ${TCCOPTS} -Fj -o throw.j throw.cc

vtable.j: vtable.p
	${TNC} vtable.p vtable.j

clobber: clean
	${REMOVE} ${SYS_FILES}
