all: calc

clean:
	rm -f lex.yy.o lex.yy.c calc.o calc.c calc.h calc

calc: lex.yy.o calc.o
	$(CC) -o calc lex.yy.o calc.o

calc.c: calc.act calc.sid
	sid calc.sid calc.act calc.c calc.h

lex.yy.c: lex.l calc.c
	lex lex.l

