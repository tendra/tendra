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

OBJS=		builder.o contents.o extract.o linker.o

all: libfrontend.a

libfrontend.a: ${OBJS}
	${AR} r $@ ${OBJS}
	${RANLIB} $@

clean:
	${REMOVE} libfrontend.a ${OBJS}

