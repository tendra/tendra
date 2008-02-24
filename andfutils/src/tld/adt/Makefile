# $Id$

AR = ar
RANLIB = ranlib
CFLAGS =
REMOVE = rm -f

TARGETS = arg-data.o map-entry.o name-entry.o name-table.o shape-table.o \
	tdf-write.o unit-table.o capsule.o map-table.o name-key.o shape-entry.o \
	tdf-read.o unit-entry.o library.o

adt.a: $(TARGETS)
	$(AR) r $@ $(TARGETS)
	$(RANLIB) $@

clean:
	$(REMOVE) adt.a $(TARGETS)

