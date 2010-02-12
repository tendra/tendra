# $Id$

.include "Makefile.inc"


TCCOPTS=-Y${OBJ_DIR}/${ENVIRONMENT}/build -yTENDRA_BASEDIR="${OBJ_DIR}/src" -Yc++ -I${SRC}

SYS_FILES=basic.j ptr_func.j ptr_mem.j throw.j vtable.j


all:: ${SYS_FILES}

basic.j: basic.cc
	${TCC} ${TCCOPTS} -Fj -o basic.j basic.cc

ptr_func.j: ptr_func.p
	${TNC} ptr_func.p ptr_func.j

ptr_mem.j: ptr_mem.p
	${TNC} ptr_mem.p ptr_mem.j

throw.j: throw.cc
	${TCC} ${TCCOPTS} -Fj -o throw.j throw.cc

vtable.j: vtable.p
	${TNC} vtable.p vtable.j

CLEAN_EXTRA= ${SYS_FILES}

