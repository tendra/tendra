# $Id$

TARGETS=bitvec.o cstring.o dalloc.o dstring.o error-file.o error.o \
	exception.o istream.o ostream.o syntax.o

REMOVE=rm -f

all: eds.a ${TARGETS}

clean:
	${REMOVE} eds.a ${TARGETS}

eds.a: ${TARGETS}
	ar r $@ ${TARGETS}
	ranlib $@

