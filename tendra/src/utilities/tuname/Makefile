# $Id$

# Set up the build infrastructure
.include "../../../mk/tendra.build.mk"

# Standard directories and files
SRCX = ${.CURDIR}/../shared

CC ?= tcc
TCCOPTS = -Ysystem
CCOPTS = ${TCCOPTS} -I${SRCX}
LIBS =

.include "../../../mk/tendra.compiler.mk"

# Dependencies and construction rules

NAME = tuname

CFILES = tuname.c

${NAME} : ${CFILES}
	@${ECHO} ${BASE_DIR}
	${CC} ${CCOPTS} -o ${NAME} ${CFILES} ${LIBS}

all: ${NAME}
	@${ECHO} all done
