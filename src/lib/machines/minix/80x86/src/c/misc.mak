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
	$(LIBRARY)(iolib.o) \
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

$(LIBRARY)(iolib.o):	$(SRC)/iolib.s
	$(CC1) $(SRC)/iolib.s

$(LIBRARY)(oneC_sum.o):	$(SRC)/oneC_sum.s
	$(CC1) $(SRC)/oneC_sum.s
