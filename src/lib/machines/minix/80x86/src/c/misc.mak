# Makefile for lib/i386/misc.

SRC=/usr/src/lib/i386/misc
LIBRARY=$(NAME)
CCCP=cc -E
CC1=tcc -Ysystem -c

all: $(LIBRARY)

OBJECTS	= \
	$(LIBRARY)(alloca.o) \
	$(LIBRARY)(get_bp.o) \
	$(LIBRARY)(getprocessor.o) \
	$(LIBRARY)(io_inb.o) \
	$(LIBRARY)(io_inl.o) \
	$(LIBRARY)(io_insb.o) \
	$(LIBRARY)(io_insl.o) \
	$(LIBRARY)(io_insw.o) \
	$(LIBRARY)(io_intr.o) \
	$(LIBRARY)(io_inw.o) \
	$(LIBRARY)(io_outb.o) \
	$(LIBRARY)(io_outl.o) \
	$(LIBRARY)(io_outsb.o) \
	$(LIBRARY)(io_outsl.o) \
	$(LIBRARY)(io_outsw.o) \
	$(LIBRARY)(io_outw.o) \
	$(LIBRARY)(oneC_sum.o) \

$(LIBRARY):	$(OBJECTS)
	aal cr $@ *.o
	rm *.o

$(LIBRARY)(alloca.o):	$(SRC)/alloca.s
	$(CCCP) $(SRC)/alloca.s > alloca.s
	$(CC1) alloca.s
	rm alloca.s

$(LIBRARY)(get_bp.o):	$(SRC)/get_bp.s
	$(CC1) $(SRC)/get_bp.s

$(LIBRARY)(getprocessor.o):	$(SRC)/getprocessor.s
	$(CC1) $(SRC)/getprocessor.s

$(LIBRARY)(io_inb.o):	$(SRC)/io_inb.s
	$(CC1) $(SRC)/io_inb.s

$(LIBRARY)(io_inl.o):	$(SRC)/io_inl.s
	$(CC1) $(SRC)/io_inl.s

$(LIBRARY)(io_insb.o):	$(SRC)/io_insb.s
	$(CC1) $(SRC)/io_insb.s

$(LIBRARY)(io_insl.o):	$(SRC)/io_insl.s
	$(CC1) $(SRC)/io_insl.s

$(LIBRARY)(io_insw.o):	$(SRC)/io_insw.s
	$(CC1) $(SRC)/io_insw.s

$(LIBRARY)(io_intr.o):	$(SRC)/io_intr.s
	$(CC1) $(SRC)/io_intr.s

$(LIBRARY)(io_inw.o):	$(SRC)/io_inw.s
	$(CC1) $(SRC)/io_inw.s

$(LIBRARY)(io_outb.o):	$(SRC)/io_outb.s
	$(CC1) $(SRC)/io_outb.s

$(LIBRARY)(io_outl.o):	$(SRC)/io_outl.s
	$(CC1) $(SRC)/io_outl.s

$(LIBRARY)(io_outsb.o):	$(SRC)/io_outsb.s
	$(CC1) $(SRC)/io_outsb.s

$(LIBRARY)(io_outsl.o):	$(SRC)/io_outsl.s
	$(CC1) $(SRC)/io_outsl.s

$(LIBRARY)(io_outsw.o):	$(SRC)/io_outsw.s
	$(CC1) $(SRC)/io_outsw.s

$(LIBRARY)(io_outw.o):	$(SRC)/io_outw.s
	$(CC1) $(SRC)/io_outw.s

$(LIBRARY)(oneC_sum.o):	$(SRC)/oneC_sum.s
	$(CC1) $(SRC)/oneC_sum.s
