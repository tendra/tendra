# $Id$

SRC2=	${BASE_DIR}/lib/machines/common/src

TCCOPTS=	-Ysystem
CCOPTS=		${TCCOPTS} -I${SRC2}

PROG=	dyninit
SRCS=	dyninit.c

all: dyninit TDFpower.o
	./${OBJ_SDIR}/dyninit TDFpower.o
	@${ECHO} all done

.include "../../../Makefile.inc"
