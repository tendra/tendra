# Makefile for lib/end.

SRC=/usr/src/lib/end
LIBRARY=../end.a
CCCP=cc -E
CC1=tcc -Ysystem -c

all: $(LIBRARY)

OBJECTS	= \
	$(LIBRARY)(edata.o) \
	$(LIBRARY)(em_end.o) \
	$(LIBRARY)(end.o) \
	$(LIBRARY)(etext.o) \

$(LIBRARY):	$(OBJECTS)
	aal cr $@ *.o
	rm *.o

$(LIBRARY)(edata.o):	$(SRC)/edata.s
	$(CCCP) $(SRC)/edata.s > edata.s
	$(CC1) edata.s
	rm edata.s

$(LIBRARY)(em_end.o):	$(SRC)/em_end.s
	$(CCCP) $(SRC)/em_end.s > em_end.s
	$(CC1) em_end.s
	rm em_end.s

$(LIBRARY)(end.o):	$(SRC)/end.s
	$(CCCP) $(SRC)/end.s > end.s
	$(CC1) end.s
	rm end.s

$(LIBRARY)(etext.o):	$(SRC)/etext.s
	$(CCCP) $(SRC)/etext.s > etext.s
	$(CC1) etext.s
	rm etext.s
