# Makefile for lib/timers.

SRC=/usr/src/lib/timers
LIBRARY=$(NAME)
CC1=tcc -Ysystem -c

all: $(LIBRARY)

OBJECTS	= \
	$(LIBRARY)(tmrs_set.o) \
	$(LIBRARY)(tmrs_clr.o) \
	$(LIBRARY)(tmrs_exp.o) \

$(LIBRARY):	$(OBJECTS)
	aal cr $@ *.o
	rm *.o

$(LIBRARY)(tmrs_set.o):	$(SRC)/tmrs_set.c
	$(CC1) $(SRC)/tmrs_set.c

$(LIBRARY)(tmrs_clr.o):	$(SRC)/tmrs_clr.c
	$(CC1) $(SRC)/tmrs_clr.c

$(LIBRARY)(tmrs_exp.o):	$(SRC)/tmrs_exp.c
	$(CC1) $(SRC)/tmrs_exp.c

