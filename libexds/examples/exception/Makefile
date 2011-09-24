# $Id$

TARGETS = exception.o

CFLAGS = -I ../../include
LIBS = -L ../../src -lexds

RMFILE = rm -f

all: exception

clean:
	${RMFILE} exception ${TARGETS}

exception: $(TARGETS)
	$(CC) $(CFLAGS) $(LIBS) -o $@ $(TARGETS)

