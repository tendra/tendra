# Makefile for lib/i386/string.

SRC=/usr/src/lib/i386/string
LIBRARY=$(NAME)
CC1=tcc -Ysystem -c

all: $(LIBRARY)

OBJECTS	= \
	$(LIBRARY)(_memmove.o) \
	$(LIBRARY)(_strncat.o) \
	$(LIBRARY)(_strncmp.o) \
	$(LIBRARY)(_strncpy.o) \
	$(LIBRARY)(_strnlen.o) \
	$(LIBRARY)(bcmp.o) \
	$(LIBRARY)(bcopy.o) \
	$(LIBRARY)(bzero.o) \
	$(LIBRARY)(index.o) \
	$(LIBRARY)(memchr.o) \
	$(LIBRARY)(memcmp.o) \
	$(LIBRARY)(memcpy.o) \
	$(LIBRARY)(memmove.o) \
	$(LIBRARY)(memset.o) \
	$(LIBRARY)(rindex.o) \
	$(LIBRARY)(strcat.o) \
	$(LIBRARY)(strchr.o) \
	$(LIBRARY)(strcmp.o) \
	$(LIBRARY)(strcpy.o) \
	$(LIBRARY)(strlen.o) \
	$(LIBRARY)(strncat.o) \
	$(LIBRARY)(strncmp.o) \
	$(LIBRARY)(strncpy.o) \
	$(LIBRARY)(strnlen.o) \
	$(LIBRARY)(strrchr.o) \

$(LIBRARY):	$(OBJECTS)
	aal cr $@ *.o
	rm *.o

$(LIBRARY)(_memmove.o):	$(SRC)/_memmove.s
	$(CC1) $(SRC)/_memmove.s

$(LIBRARY)(_strncat.o):	$(SRC)/_strncat.s
	$(CC1) $(SRC)/_strncat.s

$(LIBRARY)(_strncmp.o):	$(SRC)/_strncmp.s
	$(CC1) $(SRC)/_strncmp.s

$(LIBRARY)(_strncpy.o):	$(SRC)/_strncpy.s
	$(CC1) $(SRC)/_strncpy.s

$(LIBRARY)(_strnlen.o):	$(SRC)/_strnlen.s
	$(CC1) $(SRC)/_strnlen.s

$(LIBRARY)(bcmp.o):	$(SRC)/bcmp.s
	$(CC1) $(SRC)/bcmp.s

$(LIBRARY)(bcopy.o):	$(SRC)/bcopy.s
	$(CC1) $(SRC)/bcopy.s

$(LIBRARY)(bzero.o):	$(SRC)/bzero.s
	$(CC1) $(SRC)/bzero.s

$(LIBRARY)(index.o):	$(SRC)/index.s
	$(CC1) $(SRC)/index.s

$(LIBRARY)(memchr.o):	$(SRC)/memchr.s
	$(CC1) $(SRC)/memchr.s

$(LIBRARY)(memcmp.o):	$(SRC)/memcmp.s
	$(CC1) $(SRC)/memcmp.s

$(LIBRARY)(memcpy.o):	$(SRC)/memcpy.s
	$(CC1) $(SRC)/memcpy.s

$(LIBRARY)(memmove.o):	$(SRC)/memmove.s
	$(CC1) $(SRC)/memmove.s

$(LIBRARY)(memset.o):	$(SRC)/memset.s
	$(CC1) $(SRC)/memset.s

$(LIBRARY)(rindex.o):	$(SRC)/rindex.s
	$(CC1) $(SRC)/rindex.s

$(LIBRARY)(strcat.o):	$(SRC)/strcat.s
	$(CC1) $(SRC)/strcat.s

$(LIBRARY)(strchr.o):	$(SRC)/strchr.s
	$(CC1) $(SRC)/strchr.s

$(LIBRARY)(strcmp.o):	$(SRC)/strcmp.s
	$(CC1) $(SRC)/strcmp.s

$(LIBRARY)(strcpy.o):	$(SRC)/strcpy.s
	$(CC1) $(SRC)/strcpy.s

$(LIBRARY)(strlen.o):	$(SRC)/strlen.s
	$(CC1) $(SRC)/strlen.s

$(LIBRARY)(strncat.o):	$(SRC)/strncat.s
	$(CC1) $(SRC)/strncat.s

$(LIBRARY)(strncmp.o):	$(SRC)/strncmp.s
	$(CC1) $(SRC)/strncmp.s

$(LIBRARY)(strncpy.o):	$(SRC)/strncpy.s
	$(CC1) $(SRC)/strncpy.s

$(LIBRARY)(strnlen.o):	$(SRC)/strnlen.s
	$(CC1) $(SRC)/strnlen.s

$(LIBRARY)(strrchr.o):	$(SRC)/strrchr.s
	$(CC1) $(SRC)/strrchr.s
