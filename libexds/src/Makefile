# $Id$

PREFIX ?= /usr/local

LIBTOOL = libtool
CC = ${LIBTOOL} --mode=compile cc
LINK = ${LIBTOOL} --mode=link cc
CFLAGS = -I ../include

TARGETS = bitvec.o cstring.o dalloc.o dstring.o error-file.o error.o \
	exception.o istream.o ostream.o syntax.o \
	bistream.o bostream.o cstring-list.o nstring-list.o

LTARGETS = bitvec.lo cstring.lo dalloc.lo dstring.lo error-file.lo error.lo \
	exception.lo istream.lo ostream.lo syntax.lo \
	bistream.lo bostream.lo cstring-list.lo nstring-list.lo


REMOVE = rm -f

all: libexds.la ${TARGETS}

clean:
	${REMOVE} libexds.la ${TARGETS} ${LTARGETS}

install: libexds.la
	install -m 755 libexds.la ${PREFIX}/lib

libexds.la: ${TARGETS}
	# TODO -rpath for install:
	${LINK} -o libexds.la ${LTARGETS}

