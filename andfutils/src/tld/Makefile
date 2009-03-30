# $Id$

CC?=		cc
REMOVE?=	rm -f

EXDSLIBDIR?=	../../../libexds/src
EXDSINCDIR?=	../../../libexds/include
SHRDINCDIR?=	../shared

CPPFLAGS+=	-I${EXDSINCDIR} -I${SHRDINCDIR} -I.
CFLAGS+=	${CPPFLAGS}
LDFLAGS+=	-Ladt -Lfrontend -Lerrors -L${EXDSLIBDIR}
LIBS=		-ladt -lfrontend -lerrors -Wl,-Bstatic -lexds -Wl,-Bdynamic

#TCCOPTS=	-Yansi -Xs # keep for re-integration with tcc

PROG=		${.CURDIR:T}
OBJS=		arg-parse.o debug.o file-name.o main.o rename-file.o syntax.o \
		tdf.o

${PROG}: lib-depends ${OBJS}
	${CC} ${LDFLAGS} -o ${PROG} ${OBJS} ${LIBS}

lib-depends:
	cd errors && ${MAKE}
	cd adt && ${MAKE}
	cd frontend && ${MAKE}
	cd ${EXDSLIBDIR} && ${MAKE}

clean:
	${REMOVE} ${PROG} ${OBJS}
	cd errors && ${MAKE} clean
	cd adt && ${MAKE} clean
	cd frontend && ${MAKE} clean
	# cd ${EXDSLIBDIR} && ${MAKE} clean # XXX: clean here as well?
