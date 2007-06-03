
all: brf

brf: main.o
	$(CC) $(CFLAGS) $(LIBS) -o brf main.o

main.o: main.c braille.c
	$(CC) -c $(CFLAGS) main.c

braille.c: braille.lxi
	lexi braille.lxi > braille.c

