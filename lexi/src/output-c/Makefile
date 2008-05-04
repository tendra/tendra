# $Id$

TARGETS = c-output.o

REMOVE = rm -f
AR = ar
RANLIB = ranlib

CFLAGS += -I ../shared -I ..

all: output-c.a

clean:
	${REMOVE} ${TARGETS} output-c.a

output-c.a: ${TARGETS}
	${AR} r $@ ${TARGETS}
	${RANLIB} $@

c-output.o: c-output.h

