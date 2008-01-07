# $Id$

TARGETS = dot-output.o

REMOVE = rm -f
AR = ar
RANLIB = ranlib

CFLAGS += -I ../shared/error -I ../shared/xalloc -I ..

all: output-dot.a

clean:
	${REMOVE} ${TARGETS} output-dot.a

output-dot.a: ${TARGETS}
	${AR} r $@ ${TARGETS}
	${RANLIB} $@

dot-output.o: dot-output.h

