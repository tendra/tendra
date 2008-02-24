# $Id$

AR = ar
RANLIB = ranlib
CFLAGS =
REMOVE = rm -f

TARGETS = builder.o contents.o extract.o linker.o

frontend.a: $(TARGETS)
	$(AR) r $@ $(TARGETS)
	$(RANLIB) $@

clean:
	$(REMOVE) frontend.a $(TARGETS)

