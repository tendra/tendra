# $Id$

.include <tendra.compler.mk>

BASE=/u/g/release/Source
SRC=${BASE}/src/lib/machines/common/src

TCCOPTS=-Ysystem
RMFILE=rm -f
MOVE=mv
COPY=cp
ECHO=echo
SHELL=/bin/sh

all : crtp_n.o
	@${ECHO} all done

crtp_n.o : ${SRC}/crtp_n.tpl
	${TCC} -Ypl_tdf -c ${SRC}/crtp_n.tpl

clean :
	${RMFILE} core

clobber : clean
	${RMFILE} crtp_n.o
