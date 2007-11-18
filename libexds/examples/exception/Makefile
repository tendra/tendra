# $Id$

TARGETS = exception.o

CFLAGS = -I ../../include
LIBS = -L ../../src -lexds

REMOVE = rm -f

all: exception

clean:
	${REMOVE} exception ${TARGETS}

exception: $(TARGETS)
	$(CC) $(CFLAGS) $(LIBS) -o $@ $(TARGETS)

