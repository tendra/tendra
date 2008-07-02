# $Id$

TARGETS=test-main.o

REMOVE=rm -f

all: lang-test.a

clean:
	${REMOVE} lang-test.a ${TARGETS}

maintainer-clean:

lang-test.a: ${TARGETS}
	ar r $@ ${TARGETS}
	ranlib $@

