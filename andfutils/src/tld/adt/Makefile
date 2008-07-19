# $Id$

AR?=		ar
CC?=		cc
RANLIB?=	ranlib
REMOVE?=	rm -f

EXDSLIBDIR?=
EXDSINCDIR?=	../../../../libexds/include
SHRDINCDIR?=	../../../../shared

CPPFLAGS+=	-I${EXDSINCDIR} -I${SHRDINCDIR} -I..
CFLAGS+=	${CPPFLAGS}

OBJS=		arg-data.o map-entry.o name-entry.o name-table.o shape-table.o \
		tdf-write.o unit-table.o capsule.o map-table.o name-key.o \
		shape-entry.o tdf-read.o unit-entry.o library.o
all: libadt.a

libadt.a: ${OBJS}
	${AR} r $@ ${OBJS}
	${RANLIB} $@

clean:
	${REMOVE} libadt.a ${OBJS}

