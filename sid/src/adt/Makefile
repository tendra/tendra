# $Id$

TARGETS=action.o basic.o cstring-list.o entry-list.o entry.o key.o \
	name.o non-local.o rstack.o scope.o table.o type.o types.o

REMOVE=rm -f

all: adt.a ${TARGETS}

clean:
	${REMOVE} adt.a $(TARGETS)

adt.a: ${TARGETS}
	ar r $@ ${TARGETS}
	ranlib $@

