# $Id$
# TODO This ought to use the usual build system instead.

CC = tcc
CFLAGS = -Xp -Yansi

test: list_test
	./list_test

clean:
	rm -f *_test

all:

list_test: list_test.c ../list.c ../utility.c
	$(CC) -o $@ $(CFLAGS) ../list.c ../utility.c list_test.c

