# Makefile for lib/util.

SRC=/usr/src/lib/util
LIBRARY=$(NAME)
CC1=tcc -Ysystem -c -I$(SRC)

all: $(LIBRARY)

OBJECTS	= \
	$(LIBRARY)(openpty.o) \

$(LIBRARY):	$(OBJECTS)
	aal cr $@ *.o
	rm *.o

$(LIBRARY)(openpty.o):	$(SRC)/openpty.c
	$(CC1) $(SRC)/openpty.c
