# Makefile for lib/math.

SRC=/usr/src/lib/math
SRC2=/usr/src/lib/i386/em
LIBRARY=$(NAME)
CC1=tcc -Ysystem -c -I$(SRC)

all: $(LIBRARY)

OBJECTS	= \
	$(LIBRARY)(asin.o) \
	$(LIBRARY)(atan.o) \
	$(LIBRARY)(atan2.o) \
	$(LIBRARY)(ceil.o) \
	$(LIBRARY)(exp.o) \
	$(LIBRARY)(fabs.o) \
	$(LIBRARY)(floor.o) \
	$(LIBRARY)(fmod.o) \
	$(LIBRARY)(frexp.o) \
	$(LIBRARY)(hugeval.o) \
	$(LIBRARY)(isnan.o) \
	$(LIBRARY)(ldexp.o) \
	$(LIBRARY)(log.o) \
	$(LIBRARY)(log10.o) \
	$(LIBRARY)(modf.o) \
	$(LIBRARY)(pow.o) \
	$(LIBRARY)(sin.o) \
	$(LIBRARY)(sinh.o) \
	$(LIBRARY)(sqrt.o) \
	$(LIBRARY)(tan.o) \
	$(LIBRARY)(tanh.o) \
	$(LIBRARY)(em_fp8087.o)

$(LIBRARY):	$(OBJECTS)
	aal cr $@ *.o
	rm *.o

$(LIBRARY)(asin.o):	$(SRC)/asin.c
	$(CC1) $(SRC)/asin.c

$(LIBRARY)(atan.o):	$(SRC)/atan.c
	$(CC1) $(SRC)/atan.c

$(LIBRARY)(atan2.o):	$(SRC)/atan2.c
	$(CC1) $(SRC)/atan2.c

$(LIBRARY)(ceil.o):	$(SRC)/ceil.c
	$(CC1) $(SRC)/ceil.c

$(LIBRARY)(exp.o):	$(SRC)/exp.c
	$(CC1) $(SRC)/exp.c

$(LIBRARY)(fabs.o):	$(SRC)/fabs.c
	$(CC1) $(SRC)/fabs.c

$(LIBRARY)(floor.o):	$(SRC)/floor.c
	$(CC1) $(SRC)/floor.c

$(LIBRARY)(fmod.o):	$(SRC)/fmod.c
	$(CC1) $(SRC)/fmod.c

$(LIBRARY)(frexp.o):	$(SRC1)/frexp.s
	$(CC1) $(SRC1)/frexp.s

$(LIBRARY)(hugeval.o):	$(SRC)/hugeval.c
	$(CC1) $(SRC)/hugeval.c

$(LIBRARY)(isnan.o):	$(SRC)/isnan.c
	$(CC1) $(SRC)/isnan.c

$(LIBRARY)(ldexp.o):	$(SRC)/ldexp.c
	$(CC1) $(SRC)/ldexp.c

$(LIBRARY)(log.o):	$(SRC)/log.c
	$(CC1) $(SRC)/log.c

$(LIBRARY)(log10.o):	$(SRC)/log10.c
	$(CC1) $(SRC)/log10.c

$(LIBRARY)(modf.o):	$(SRC1)/modf.s
	$(CC1) $(SRC1)/modf.s

$(LIBRARY)(pow.o):	$(SRC)/pow.c
	$(CC1) $(SRC)/pow.c

$(LIBRARY)(sin.o):	$(SRC)/sin.c
	$(CC1) $(SRC)/sin.c

$(LIBRARY)(sinh.o):	$(SRC)/sinh.c
	$(CC1) $(SRC)/sinh.c

$(LIBRARY)(sqrt.o):	$(SRC)/sqrt.c
	$(CC1) $(SRC)/sqrt.c

$(LIBRARY)(tan.o):	$(SRC)/tan.c
	$(CC1) $(SRC)/tan.c

$(LIBRARY)(tanh.o):	$(SRC)/tanh.c
	$(CC1) $(SRC)/tanh.c

$(LIBRARY)(em_fp8087.o):	$(SRC2)/em_fp8087.s
	$(CC1) $(SRC2)/em_fp8087.s

