# Makefile for lib/i386/rts.

SRC=/usr/src/lib/i386/rts
LIBRARY=$(NAME)
CC1=tcc -Ysystem -c

all: $(LIBRARY)

OBJECTS	= \
	$(LIBRARY)(setjmp.o) \
	$(LIBRARY)(__sigreturn.o) \
	$(LIBRARY)(_ipc.o) \
	$(LIBRARY)(brksize.o) \

$(LIBRARY):	$(OBJECTS)
	aal cr $@ *.o
	rm *.o

$(LIBRARY)(setjmp.o):	$(SRC1)/setjmp.s
	$(CC1) $(SRC1)/setjmp.s

$(LIBRARY)(__sigreturn.o):	$(SRC)/__sigreturn.s
	$(CC1) $(SRC)/__sigreturn.s

$(LIBRARY)(_ipc.o):	$(SRC)/_ipc.s
	$(CC1) $(SRC)/_ipc.s

$(LIBRARY)(brksize.o):	$(SRC)/brksize.s
	$(CC1) $(SRC)/brksize.s
