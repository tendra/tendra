# $Id$

CC = cc
CFLAGS = -I ../../include
LINK = ld -shared
HARNESS = harness

TARGETS = dstring.o

TESTTARGETS = libdstring.so

REMOVE = rm -f

all: ${TESTTARGETS}

test: ${TESTTARGETS}
	${HARNESS} ${TESTTARGETS}

clean:
	$(REMOVE) ${TARGETS}

${TESTTARGETS}: ${TARGETS}
	for target in ${TARGETS}; do \
		${LINK} -o "lib`echo $$target | sed 's/\.o$$/.so/'`" $$target \
			-L ../../src -lexds; \
	done

