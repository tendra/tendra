# $Id$

# Set up the build infrastructure
.include "../../../mk/tendra.build.mk"

# Standard directories and files
SRC = ${.CURDIR}
SRCX = ${SRC}/../shared

CC ?= tcc
TCCOPTS = -Ysystem
CCOPTS = ${TCCOPTS} -I${SRCX}
LIBS =

.include "../../../mk/tendra.compiler.mk"

# Dependencies and construction rules

NAME = tuname

${NAME} : ${SRC}/tuname.c ${SRCX}/ossg.h
	@${ECHO} ${BASE_DIR}
	${CC} ${CCOPTS} -o ${NAME} ${SRC}/tuname.c ${LIBS}

all: ${NAME}
	@${ECHO} all done

extra:
	@${ECHO} done

clean:
	${REMOVE} ${NAME}.core core ${NAME}
