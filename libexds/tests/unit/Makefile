# $Id$

LIBTOOL = libtool
CC = ${LIBTOOL} --mode=compile cc
LINK = ${LIBTOOL} --mode=link cc
CFLAGS = -I ../../include

TARGETS = dstring.o

TESTTARGETS = dstring.la

REMOVE = rm -f
HARNESS = harness

all: ${TESTTARGETS}

test: ${TESTTARGETS}
	${HARNESS} .libs/*.so

clean:
	$(REMOVE) ${TARGETS}
	${REMOVE} *.lo
	${REMOVE} *.la
	$(REMOVE) -r .libs

${TESTTARGETS}: ${TARGETS}
	for target in ${TESTTARGETS}; do \
		${LINK} -o lib$$target `echo $$target | sed 's/\.la/\.lo/'` -rpath $$PWD ../../src/libexds.la; \
	done

