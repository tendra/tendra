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

SRCS = tuname.c

${NAME}: ${SRCS}
	@${ECHO} ${BASE_DIR}
	${CC} ${CCOPTS} -o ${NAME} ${SRCS} ${LIBS}

all: ${NAME}
	@${ECHO} all done
