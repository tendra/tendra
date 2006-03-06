# Makefile for lib/regex.

SRC=/usr/src/lib/regex
LIBRARY=$(NAME)
CC1=tcc -Ysystem -c

all: $(LIBRARY)

OBJ	= \
	$(LIBRARY)(regcomp.o) \
	$(LIBRARY)(regerror.o) \
	$(LIBRARY)(regexec.o) \
	$(LIBRARY)(regfree.o) \

$(LIBRARY):	$(OBJ)
	aal cr $@ *.o
	rm *.o

$(LIBRARY)(regcomp.o):	$(SRC)/regcomp.c
	chmem  =663552 $(MACH_BASE)/bin/tdfc2
	chmem =1933312 $(MACH_BASE)/bin/trans
	$(CC1) $(SRC)/regcomp.c
	chmem  =655360 $(MACH_BASE)/bin/tdfc2
	chmem =1441792 $(MACH_BASE)/bin/trans

$(LIBRARY)(regerror.o):	$(SRC)/regerror.c
	$(CC1) $(SRC)/regerror.c

$(LIBRARY)(regexec.o):	$(SRC)/regexec.c
	$(CC1) $(SRC)/regexec.c

$(LIBRARY)(regfree.o):	$(SRC)/regfree.c
	$(CC1) $(SRC)/regfree.c
