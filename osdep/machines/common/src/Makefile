BASE=/u/g/release/Source
SRC=${BASE}/src/lib/machines/common/src

CC=tcc
TCCOPTS=-Ysystem
REMOVE=rm -f
MOVE=mv
COPY=cp
ECHO=echo
SHELL=/bin/sh

# Environments are not yet installed, so we use them in-situ.
TCCOPTS+=	--SED${OBJ_DIR}/env --CFE

all : crtp_n.o
	@${ECHO} all done

crtp_n.o : ${SRC}/crtp_n.tpl
	${CC} -Ypl_tdf -c ${SRC}/crtp_n.tpl

clean :
	${REMOVE} core

clobber : clean
	${REMOVE} crtp_n.o
