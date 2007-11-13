# $Id$

LIBTOOL = libtool
CC = ${LIBTOOL} --mode=compile cc
LINK = ${LIBTOOL} --mode=link cc

TARGETS = bitvec.o cstring.o dalloc.o dstring.o error-file.o error.o \
	exception.o istream.o ostream.o syntax.o

LTARGETS = bitvec.lo cstring.lo dalloc.lo dstring.lo error-file.lo error.lo \
	exception.lo istream.lo ostream.lo syntax.lo


REMOVE = rm -f

all: libeds.la ${TARGETS}

clean:
	${REMOVE} libeds.a ${TARGETS} ${LTARGETS}

libeds.la: ${TARGETS}
	# TODO -rpath for install:
	${LINK} -o libeds.la ${LTARGETS}

