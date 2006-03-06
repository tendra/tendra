# Makefile for lib/zlib-1.2.3

SRC=/usr/src/lib/zlib-1.2.3
SRC1=${BASE}/src/lib/machines/minix/80x86/src/z
LIBRARY=$(NAME)

CFLAGS	=-D_MINIX=1 -D_POSIX_SOURCE=1
CC1	=tcc -Ysystem $(CFLAGS) -I$(SRC) -c

all: $(LIBRARY)

OBJECTS	= \
	$(LIBRARY)(adler32.o) \
	$(LIBRARY)(compress.o) \
	$(LIBRARY)(crc32.o) \
	$(LIBRARY)(gzio.o) \
	$(LIBRARY)(uncompr.o) \
	$(LIBRARY)(deflate.o) \
	$(LIBRARY)(trees.o) \
	$(LIBRARY)(zutil.o) \
	$(LIBRARY)(inflate.o) \
	$(LIBRARY)(infback.o) \
	$(LIBRARY)(inftrees.o) \
	$(LIBRARY)(inffast.o) \

$(LIBRARY):	$(OBJECTS)
	aal cr $@ *.o
	rm *.o

$(LIBRARY)(adler32.o):	$(SRC)/adler32.c
	$(CC1) $(SRC)/adler32.c

$(LIBRARY)(compress.o):	$(SRC)/compress.c
	$(CC1) $(SRC)/compress.c

$(LIBRARY)(crc32.o):	$(SRC)/crc32.c $(SRC1)/crc32.patch
	cp $(SRC)/crc32.c . \
	&& patch crc32.c $(SRC1)/crc32.patch \
	&& $(CC1) crc32.c \
	&& rm -f crc32.c crc32.c~

$(LIBRARY)(gzio.o):	$(SRC)/gzio.c
	$(CC1) $(SRC)/gzio.c

$(LIBRARY)(uncompr.o):	$(SRC)/uncompr.c
	$(CC1) $(SRC)/uncompr.c

$(LIBRARY)(deflate.o):	$(SRC)/deflate.c
	$(CC1) $(SRC)/deflate.c

$(LIBRARY)(trees.o):	$(SRC)/trees.c
	chmem =786432 $(MACH_BASE)/bin/tdfc2
	chmem =1966080 $(MACH_BASE)/bin/trans
	$(CC1) $(SRC)/trees.c
	chmem =655360 $(MACH_BASE)/bin/tdfc2
	chmem =1441792 $(MACH_BASE)/bin/trans

$(LIBRARY)(zutil.o):	$(SRC)/zutil.c
	$(CC1) $(SRC)/zutil.c

$(LIBRARY)(inflate.o):	$(SRC)/inflate.c
	chmem =851968 $(MACH_BASE)/bin/tdfc2
	$(CC1) $(SRC)/inflate.c
	chmem =655360 $(MACH_BASE)/bin/tdfc2

$(LIBRARY)(infback.o):	$(SRC)/infback.c
	chmem =720896 $(MACH_BASE)/bin/tdfc2
	$(CC1) $(SRC)/infback.c
	chmem =655360 $(MACH_BASE)/bin/tdfc2

$(LIBRARY)(inftrees.o):	$(SRC)/inftrees.c
	$(CC1) $(SRC)/inftrees.c

$(LIBRARY)(inffast.o):	$(SRC)/inffast.c
	$(CC1) $(SRC)/inffast.c
