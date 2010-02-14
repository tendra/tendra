# $Id$

CC?=		cc
REMOVE?=	rm -f

EXDSLIBDIR?=	../../../libexds/src
EXDSINCDIR?=	../../../libexds/include
SHRDINCDIR?=	../shared

CPPFLAGS+=	-I${EXDSINCDIR} -I${SHRDINCDIR} -I.
#CFLAGS+=	${CPPFLAGS}  
LDFLAGS+=	-Ladt -Lfrontend -L${EXDSLIBDIR} -L${SHRDINCDIR}/error  
LIBS=		-ladt -lfrontend -Wl,-Bstatic -lexds -Wl,-Bdynamic -lerror 

#TCCOPTS=	-Yansi -Xs # keep for re-integration with tcc

PROG=		tld
OBJS=		arg-parse.o debug.o file-name.o main.o rename-file.o syntax.o \
		tdf.o fmt.o adt/capsule.o 

${PROG}: lib-depends ${OBJS}
	${CC} -o ${PROG} ${LDFLAGS} ${OBJS} ${LIBS}

lib-depends:
	cd adt && ${MAKE}
	cd frontend && ${MAKE}
	cd ${EXDSLIBDIR} && ${MAKE}

clean:
	${REMOVE} ${PROG} ${OBJS}
	cd adt && ${MAKE} clean
	cd frontend && ${MAKE} clean
	# cd ${EXDSLIBDIR} && ${MAKE} clean # XXX: clean here as well?
