# $Id$

AR=ar
RANLIB=ranlib
REMOVE=rm -f

all: error.a xalloc.a

clean:
	${REMOVE} error.o error.a xalloc.o xalloc.a

install:


error.a: error.o
	${AR} -rcus $@ error.o
	${RANLIB} $@

xalloc.a: xalloc.o
	${AR} -rcus $@ xalloc.o
	${RANLIB} $@

