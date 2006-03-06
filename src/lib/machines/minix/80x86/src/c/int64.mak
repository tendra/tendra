# Makefile for lib/i386/int64.

SRC=/usr/src/lib/i386/int64
LIBRARY=$(NAME)
CC1=tcc -Ysystem -c

all: $(LIBRARY)

OBJECTS	= \
	$(LIBRARY)(add64.o) \
	$(LIBRARY)(add64u.o) \
	$(LIBRARY)(cmp64.o) \
	$(LIBRARY)(cv64u.o) \
	$(LIBRARY)(cvu64.o) \
	$(LIBRARY)(diff64.o) \
	$(LIBRARY)(div64u.o) \
	$(LIBRARY)(ex64.o) \
	$(LIBRARY)(make64.o) \
	$(LIBRARY)(mul64u.o) \
	$(LIBRARY)(sub64.o) \
	$(LIBRARY)(sub64u.o) \

$(LIBRARY):	$(OBJECTS)
	aal cr $@ *.o
	rm *.o

$(LIBRARY)(add64.o):	$(SRC)/add64.s
	$(CC1) $(SRC)/add64.s

$(LIBRARY)(add64u.o):	$(SRC)/add64u.s
	$(CC1) $(SRC)/add64u.s

$(LIBRARY)(cmp64.o):	$(SRC)/cmp64.s
	$(CC1) $(SRC)/cmp64.s

$(LIBRARY)(cv64u.o):	$(SRC)/cv64u.s
	$(CC1) $(SRC)/cv64u.s

$(LIBRARY)(cvu64.o):	$(SRC)/cvu64.s
	$(CC1) $(SRC)/cvu64.s

$(LIBRARY)(diff64.o):	$(SRC)/diff64.s
	$(CC1) $(SRC)/diff64.s

$(LIBRARY)(div64u.o):	$(SRC)/div64u.s
	$(CC1) $(SRC)/div64u.s

$(LIBRARY)(ex64.o):	$(SRC)/ex64.s
	$(CC1) $(SRC)/ex64.s

$(LIBRARY)(make64.o):	$(SRC)/make64.s
	$(CC1) $(SRC)/make64.s

$(LIBRARY)(mul64u.o):	$(SRC)/mul64u.s
	$(CC1) $(SRC)/mul64u.s

$(LIBRARY)(sub64.o):	$(SRC)/sub64.s
	$(CC1) $(SRC)/sub64.s

$(LIBRARY)(sub64u.o):	$(SRC)/sub64u.s
	$(CC1) $(SRC)/sub64u.s
