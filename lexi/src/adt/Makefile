# $Id$

TARGETS = char.o group.o instruction.o keyword.o letter.o tree.o type.o zone.o

REMOVE = rm -f
AR = ar
RANLIB = ranlib

CFLAGS += -I ../shared -I ..

all: adt.a

clean:
	${REMOVE} ${TARGETS} adt.a

adt.a: ${TARGETS}
	${AR} r $@ ${TARGETS}
	${RANLIB} $@

