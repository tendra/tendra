# $Id$
# TODO This ought to use the usual build system instead.

CC = tcc
CFLAGS = -Xp

test: list_test startup_test
	./list_test
	./startup_test

clean:
	rm -f *_test

all:

list_test: list_test.c ../list.c ../utility.c
	$(CC) -o $@ $(CFLAGS) -Yansi ../list.c ../utility.c list_test.c

startup_test: startup_test.c ../startup.c ../list.c ../utility.c
	$(CC) -o $@ $(CFLAGS) -Yxpg3 ../startup.c ../list.c ../utility.c startup_test.c

