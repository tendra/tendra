# Makefile for lib/ansi.

# This Makefile compiles part of the C library, the functions required by the
# ANSI C standard.  This Makefile, and those in the other subdirectories use
# a little known feature of make, the ability to refer to a file within a
# library.  The construct 'libc.a(abs.o)' names the file 'abs.o' contained
# in 'libc.a'.  So the rule
#
#	libc.a(abs.o):	abs.c
#		cc -c abs.c
#		aal cr libc.a abs.o
#		rm abs.o
#
# compiles abs.c and installs the result abs.o in libc.a if abs.c is newer
# than the abs.o in the library.  This Makefile does not work like this
# precisely, it first compiles all changed source files and than installs
# them all in one 'aal' command.

# Many of the string functions in this directory are not used, because they
# have fast assembly implementations.

SRC=/usr/src/lib/ansi
LIBRARY=$(NAME)
CC1=tcc -Ysystem -c -I$(SRC)

all: $(LIBRARY)

OBJECTS	= \
	$(LIBRARY)(abort.o) \
	$(LIBRARY)(abs.o) \
	$(LIBRARY)(asctime.o) \
	$(LIBRARY)(assert.o) \
	$(LIBRARY)(atexit.o) \
	$(LIBRARY)(atof.o) \
	$(LIBRARY)(atoi.o) \
	$(LIBRARY)(atol.o) \
	$(LIBRARY)(bsearch.o) \
	$(LIBRARY)(calloc.o) \
	$(LIBRARY)(chartab.o) \
	$(LIBRARY)(clock.o) \
	$(LIBRARY)(ctime.o) \
	$(LIBRARY)(difftime.o) \
	$(LIBRARY)(div.o) \
	$(LIBRARY)(errlist.o) \
	$(LIBRARY)(exit.o) \
	$(LIBRARY)(ext_comp.o) \
	$(LIBRARY)(getenv.o) \
	$(LIBRARY)(gmtime.o) \
	$(LIBRARY)(isalnum.o) \
	$(LIBRARY)(isalpha.o) \
	$(LIBRARY)(isascii.o) \
	$(LIBRARY)(iscntrl.o) \
	$(LIBRARY)(isdigit.o) \
	$(LIBRARY)(isgraph.o) \
	$(LIBRARY)(islower.o) \
	$(LIBRARY)(isprint.o) \
	$(LIBRARY)(ispunct.o) \
	$(LIBRARY)(isspace.o) \
	$(LIBRARY)(isupper.o) \
	$(LIBRARY)(isxdigit.o) \
	$(LIBRARY)(labs.o) \
	$(LIBRARY)(ldiv.o) \
	$(LIBRARY)(localeconv.o) \
	$(LIBRARY)(localtime.o) \
	$(LIBRARY)(malloc.o) \
	$(LIBRARY)(mblen.o) \
	$(LIBRARY)(mbstowcs.o) \
	$(LIBRARY)(mbtowc.o) \
	$(LIBRARY)(misc.o) \
	$(LIBRARY)(mktime.o) \
	$(LIBRARY)(qsort.o) \
	$(LIBRARY)(raise.o) \
	$(LIBRARY)(rand.o) \
	$(LIBRARY)(setlocale.o) \
	$(LIBRARY)(sigmisc.o) \
	$(LIBRARY)(signal.o) \
	$(LIBRARY)(strcoll.o) \
	$(LIBRARY)(strcspn.o) \
	$(LIBRARY)(strerror.o) \
	$(LIBRARY)(strftime.o) \
	$(LIBRARY)(strpbrk.o) \
	$(LIBRARY)(strspn.o) \
	$(LIBRARY)(strstr.o) \
	$(LIBRARY)(strtok.o) \
	$(LIBRARY)(strtol.o) \
	$(LIBRARY)(strxfrm.o) \
	$(LIBRARY)(system.o) \
	$(LIBRARY)(tolower.o) \
	$(LIBRARY)(toupper.o) \
	$(LIBRARY)(tzset.o) \
	$(LIBRARY)(wcstombs.o) \
	$(LIBRARY)(wctomb.o) \

$(LIBRARY):	$(OBJECTS)
	aal cr $@ *.o
	rm *.o

$(LIBRARY)(abort.o):	$(SRC)/abort.c
	$(CC1) $(SRC)/abort.c

$(LIBRARY)(abs.o):	$(SRC)/abs.c
	$(CC1) $(SRC)/abs.c

$(LIBRARY)(asctime.o):	$(SRC)/asctime.c
	$(CC1) $(SRC)/asctime.c

$(LIBRARY)(assert.o):	$(SRC)/assert.c
	$(CC1) $(SRC)/assert.c

$(LIBRARY)(atexit.o):	$(SRC)/atexit.c
	$(CC1) $(SRC)/atexit.c

$(LIBRARY)(atof.o):	$(SRC)/atof.c
	$(CC1) $(SRC)/atof.c

$(LIBRARY)(atoi.o):	$(SRC)/atoi.c
	$(CC1) $(SRC)/atoi.c

$(LIBRARY)(atol.o):	$(SRC)/atol.c
	$(CC1) $(SRC)/atol.c

$(LIBRARY)(bsearch.o):	$(SRC)/bsearch.c
	$(CC1) $(SRC)/bsearch.c

$(LIBRARY)(calloc.o):	$(SRC)/calloc.c
	$(CC1) $(SRC)/calloc.c

$(LIBRARY)(chartab.o):	$(SRC)/chartab.c
	$(CC1) $(SRC)/chartab.c

$(LIBRARY)(clock.o):	$(SRC)/clock.c
	$(CC1) $(SRC)/clock.c

$(LIBRARY)(ctime.o):	$(SRC)/ctime.c
	$(CC1) $(SRC)/ctime.c

$(LIBRARY)(difftime.o):	$(SRC)/difftime.c
	$(CC1) $(SRC)/difftime.c

$(LIBRARY)(div.o):	$(SRC)/div.c
	$(CC1) $(SRC)/div.c

$(LIBRARY)(errlist.o):	$(SRC)/errlist.c
	$(CC1) $(SRC)/errlist.c

$(LIBRARY)(exit.o):	$(SRC)/exit.c
	$(CC1) $(SRC)/exit.c

$(LIBRARY)(ext_comp.o):	$(SRC)/ext_comp.c
	$(CC1) $(SRC)/ext_comp.c

$(LIBRARY)(getenv.o):	$(SRC)/getenv.c
	$(CC1) $(SRC)/getenv.c

$(LIBRARY)(gmtime.o):	$(SRC)/gmtime.c
	$(CC1) $(SRC)/gmtime.c

$(LIBRARY)(isalnum.o):	$(SRC)/isalnum.c
	$(CC1) $(SRC)/isalnum.c

$(LIBRARY)(isalpha.o):	$(SRC)/isalpha.c
	$(CC1) $(SRC)/isalpha.c

$(LIBRARY)(isascii.o):	$(SRC)/isascii.c
	$(CC1) $(SRC)/isascii.c

$(LIBRARY)(iscntrl.o):	$(SRC)/iscntrl.c
	$(CC1) $(SRC)/iscntrl.c

$(LIBRARY)(isdigit.o):	$(SRC)/isdigit.c
	$(CC1) $(SRC)/isdigit.c

$(LIBRARY)(isgraph.o):	$(SRC)/isgraph.c
	$(CC1) $(SRC)/isgraph.c

$(LIBRARY)(islower.o):	$(SRC)/islower.c
	$(CC1) $(SRC)/islower.c

$(LIBRARY)(isprint.o):	$(SRC)/isprint.c
	$(CC1) $(SRC)/isprint.c

$(LIBRARY)(ispunct.o):	$(SRC)/ispunct.c
	$(CC1) $(SRC)/ispunct.c

$(LIBRARY)(isspace.o):	$(SRC)/isspace.c
	$(CC1) $(SRC)/isspace.c

$(LIBRARY)(isupper.o):	$(SRC)/isupper.c
	$(CC1) $(SRC)/isupper.c

$(LIBRARY)(isxdigit.o):	$(SRC)/isxdigit.c
	$(CC1) $(SRC)/isxdigit.c

$(LIBRARY)(labs.o):	$(SRC)/labs.c
	$(CC1) $(SRC)/labs.c

$(LIBRARY)(ldiv.o):	$(SRC)/ldiv.c
	$(CC1) $(SRC)/ldiv.c

$(LIBRARY)(localeconv.o):	$(SRC)/localeconv.c
	$(CC1) $(SRC)/localeconv.c

$(LIBRARY)(localtime.o):	$(SRC)/localtime.c
	$(CC1) $(SRC)/localtime.c

$(LIBRARY)(malloc.o):	$(SRC)/malloc.c
	$(CC1) $(SRC)/malloc.c

$(LIBRARY)(mblen.o):	$(SRC)/mblen.c
	$(CC1) $(SRC)/mblen.c

$(LIBRARY)(mbstowcs.o):	$(SRC)/mbstowcs.c
	$(CC1) $(SRC)/mbstowcs.c

$(LIBRARY)(mbtowc.o):	$(SRC)/mbtowc.c
	$(CC1) $(SRC)/mbtowc.c

$(LIBRARY)(memchr.o):	$(SRC)/memchr.c
	$(CC1) $(SRC)/memchr.c

$(LIBRARY)(memcmp.o):	$(SRC)/memcmp.c
	$(CC1) $(SRC)/memcmp.c

$(LIBRARY)(memcpy.o):	$(SRC)/memcpy.c
	$(CC1) $(SRC)/memcpy.c

$(LIBRARY)(memmove.o):	$(SRC)/memmove.c
	$(CC1) $(SRC)/memmove.c

$(LIBRARY)(memset.o):	$(SRC)/memset.c
	$(CC1) $(SRC)/memset.c

$(LIBRARY)(misc.o):	$(SRC)/misc.c
	$(CC1) $(SRC)/misc.c

$(LIBRARY)(mktime.o):	$(SRC)/mktime.c
	$(CC1) $(SRC)/mktime.c

$(LIBRARY)(qsort.o):	$(SRC)/qsort.c
	$(CC1) $(SRC)/qsort.c

$(LIBRARY)(raise.o):	$(SRC)/raise.c
	$(CC1) $(SRC)/raise.c

$(LIBRARY)(rand.o):	$(SRC)/rand.c
	$(CC1) $(SRC)/rand.c

$(LIBRARY)(setlocale.o):	$(SRC)/setlocale.c
	$(CC1) $(SRC)/setlocale.c

$(LIBRARY)(sigmisc.o):	$(SRC)/sigmisc.c
	$(CC1) $(SRC)/sigmisc.c

$(LIBRARY)(signal.o):	$(SRC)/signal.c
	$(CC1) $(SRC)/signal.c

$(LIBRARY)(strcat.o):	$(SRC)/strcat.c
	$(CC1) $(SRC)/strcat.c

$(LIBRARY)(strchr.o):	$(SRC)/strchr.c
	$(CC1) $(SRC)/strchr.c

$(LIBRARY)(strcmp.o):	$(SRC)/strcmp.c
	$(CC1) $(SRC)/strcmp.c

$(LIBRARY)(strcoll.o):	$(SRC)/strcoll.c
	$(CC1) $(SRC)/strcoll.c

$(LIBRARY)(strcpy.o):	$(SRC)/strcpy.c
	$(CC1) $(SRC)/strcpy.c

$(LIBRARY)(strcspn.o):	$(SRC)/strcspn.c
	$(CC1) $(SRC)/strcspn.c

$(LIBRARY)(strerror.o):	$(SRC)/strerror.c
	$(CC1) $(SRC)/strerror.c

$(LIBRARY)(strftime.o):	$(SRC)/strftime.c
	$(CC1) $(SRC)/strftime.c

$(LIBRARY)(strlen.o):	$(SRC)/strlen.c
	$(CC1) $(SRC)/strlen.c

$(LIBRARY)(strncat.o):	$(SRC)/strncat.c
	$(CC1) $(SRC)/strncat.c

$(LIBRARY)(strncmp.o):	$(SRC)/strncmp.c
	$(CC1) $(SRC)/strncmp.c

$(LIBRARY)(strncpy.o):	$(SRC)/strncpy.c
	$(CC1) $(SRC)/strncpy.c

$(LIBRARY)(strpbrk.o):	$(SRC)/strpbrk.c
	$(CC1) $(SRC)/strpbrk.c

$(LIBRARY)(strrchr.o):	$(SRC)/strrchr.c
	$(CC1) $(SRC)/strrchr.c

$(LIBRARY)(strspn.o):	$(SRC)/strspn.c
	$(CC1) $(SRC)/strspn.c

$(LIBRARY)(strstr.o):	$(SRC)/strstr.c
	$(CC1) $(SRC)/strstr.c

$(LIBRARY)(strtok.o):	$(SRC)/strtok.c
	$(CC1) $(SRC)/strtok.c

$(LIBRARY)(strtol.o):	$(SRC)/strtol.c
	$(CC1) $(SRC)/strtol.c

$(LIBRARY)(strxfrm.o):	$(SRC)/strxfrm.c
	$(CC1) $(SRC)/strxfrm.c

$(LIBRARY)(system.o):	$(SRC)/system.c
	$(CC1) $(SRC)/system.c

$(LIBRARY)(tolower.o):	$(SRC)/tolower.c
	$(CC1) $(SRC)/tolower.c

$(LIBRARY)(toupper.o):	$(SRC)/toupper.c
	$(CC1) $(SRC)/toupper.c

$(LIBRARY)(tzset.o):	$(SRC)/tzset.c
	$(CC1) $(SRC)/tzset.c

$(LIBRARY)(wcstombs.o):	$(SRC)/wcstombs.c
	$(CC1) $(SRC)/wcstombs.c

$(LIBRARY)(wctomb.o):	$(SRC)/wctomb.c
	$(CC1) $(SRC)/wctomb.c
