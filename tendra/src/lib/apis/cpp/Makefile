# $Id$

API=	${.CURDIR:T}

SRC2=${BASE_DIR}/src/lib/cpp/tokens
SRC3=${BASE_DIR}/src/lib/cpp/src

TCCOPTS= -Yc++
CCOPTS= ${TCCOPTS} -I${SRC2} -I${SRC3}

.include "../Makefile.inc"

building/${API}.api/basic.j: ${SRC2}/basic.cc
	@${ECHO} "# Building basic.j"
	${TCC} ${CCOPTS} -Fj ${SRC2}/basic.cc -o ${OBJ_DIR}/${APIS}/${.TARGET:H}/basic.j

building/${API}.api/ptr_func.j: ${SRC2}/ptr_func.p
	@${ECHO} "# Building ptr_func.j"
	${TNC} ${SRC2}/ptr_func.p ${OBJ_DIR}/${APIS}/${.TARGET:H}/ptr_func.j

building/${API}.api/ptr_mem.j: ${SRC2}/ptr_mem.p
	@${ECHO} "# Building ptr_mem.j"
	${TNC} ${SRC2}/ptr_mem.p ${OBJ_DIR}/${APIS}/${.TARGET:H}/ptr_mem.j

building/${API}.api/throw.j: ${SRC2}/throw.cc
	@${ECHO} "# Building throw.j"
	${TCC} ${CCOPTS} -Fj ${SRC2}/throw.cc -o ${OBJ_DIR}/${APIS}/${.TARGET:H}/throw.j

building/${API}.api/vtable.j: ${SRC2}/vtable.p
	@${ECHO} "# Building vtable.j"
	${TNC} ${SRC2}/vtable.p ${OBJ_DIR}/${APIS}/${.TARGET:H}/vtable.j
