# A simple comment-stripping example for Lexi.
# $Id$

all: stripc

stripc: main.o
	$(CC) $(CFLAGS) $(LIBS) -o stripc main.o

main.o: main.c comments.c
	$(CC) -c $(CFLAGS) main.c

comments.c: comments.lxi
	lexi comments.lxi > comments.c

