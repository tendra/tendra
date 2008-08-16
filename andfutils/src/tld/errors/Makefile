# $Id$

BUILD_ERRORS=	./BUILD_ERRORS

SHRDINCDIR?=	../../shared
EXDSINCDIR?=    ../../../../libexds/include


CPPFLAGS+=  -I${EXDSINCDIR} -I${SHRDINCDIR} -I../adt -I..
CFLAGS+=    ${CPPFLAGS}

EFILES= \
	arg-data.e arg-parse.e builder.e capsule.e contents.e extract.e \
	for-osif.e library.e linker.e main.e name-entry.e rename-file.e \
	shape-entry.e tdf-read.e


all: liberrors.a

clean:
	rm -f liberrors.a gen-errors.o gen-errors.c gen-errors.h

liberrors.a: gen-errors.o
	ar r liberrors.a gen-errors.o

gen-errors.c: ${BUILD_ERRORS} ${EFILES}
	${PERL} ${BUILD_ERRORS} -o gen-errors ${EFILES}

