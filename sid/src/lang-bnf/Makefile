# $Id$

TARGETS=bnf-output.o bnf-out-info.o

REMOVE=rm -f

all: lang-bnf.a

clean:
	${REMOVE} lang-bnf.a ${TARGETS}

maintainer-clean:

lang-bnf.a: ${TARGETS}
	ar r $@ ${TARGETS}
	ranlib $@

