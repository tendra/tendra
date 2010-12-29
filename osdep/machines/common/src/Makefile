# $Id$

.include <tendra.situ.mk>

BASE=/u/g/release/Source
SRC=${BASE}/src/lib/machines/common/src

TCCOPTS=-Ysystem
REMOVE=rm -f
MOVE=mv
COPY=cp
ECHO=echo
SHELL=/bin/sh

all : crtp_n.o
	@${ECHO} all done

crtp_n.o : ${SRC}/crtp_n.tpl
	${TCC_IN_SITU} -Ypl_tdf -c ${SRC}/crtp_n.tpl

clean :
	${REMOVE} core

clobber : clean
	${REMOVE} crtp_n.o
