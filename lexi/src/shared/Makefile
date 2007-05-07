# $Id$

AR=ar

all: error.a xalloc.a

clean:
	rm -f error.o error.a xalloc.o xalloc.a

install:


error.a: error.o
	$(AR) -rcus $@ error.o

xalloc.a: xalloc.o
	$(AR) -rcus $@ xalloc.o

