# Makefile for lib/liby.

CFLAGS	=-O -D_MINIX -D_POSIX_SOURCE
CC1	=tcc -Ysystem $(CFLAGS) -c

SRC=/usr/src/lib/liby
LIBRARY=$(NAME)

all: $(LIBRARY)

OBJECTS	= \
	$(LIBRARY)(main.o) \
	$(LIBRARY)(yyerror.o) \

$(LIBRARY):	$(OBJECTS)
	aal cr $@ *.o
	rm *.o

$(LIBRARY)(main.o):	$(SRC)/main.c
	$(CC1) $(SRC)/main.c

$(LIBRARY)(yyerror.o):	$(SRC)/yyerror.c
	$(CC1) $(SRC)/yyerror.c
