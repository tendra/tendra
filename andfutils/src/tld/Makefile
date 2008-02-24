# $Id$

SRC1=${.CURDIR}/errors

BUILD_ERRORS = errors/BUILD_ERRORS
REMOVE = rm -f
CD = cd

TCCOPTS=	-Yansi -Xs
CCOPTS=		${TCCOPTS} -I${BASE_DIR}/${INCLUDE} -I${.CURDIR} -I${OBJ_SDIR}
LIBS=

PROG=		${.CURDIR:T}

OBJS=		gen-errors.o arg-parse.o debug.o file-name.o main.o\
		rename-file.o syntax.o tdf.o

ERR_OUT=gen-errors.c gen-errors.h

EFILES=${SRC1}/arg-data.e ${SRC1}/arg-parse.e ${SRC1}/builder.e\
 ${SRC1}/capsule.e ${SRC1}/contents.e \
 ${SRC1}/extract.e ${SRC1}/for-osif.e ${SRC1}/library.e ${SRC1}/linker.e\
 ${SRC1}/main.e ${SRC1}/name-entry.e ${SRC1}/rename-file.e\
 ${SRC1}/shape-entry.e ${SRC1}/tdf-read.e

tld: ${OBJS} adt/adt.a frontend/frontend.a
	${CC} -o tld ${OBJS} adt/adt.a frontend/frontend.a -lexds

gen-errors.c : ${BUILD_ERRORS} ${EFILES}
	${REMOVE} ${ERR_OUT};\
	${BUILD_ERRORS} -o gen-errors ${EFILES}

adt/adt.a:
	$(CD) adt && $(MAKE) adt.a

frontend/frontend.a:
	$(CD) frontend && $(MAKE) frontend.a

clean:
	$(REMOVE) tld $(OBJS)
	$(CD) adt && $(MAKE) clean
	$(CD) frontend && $(MAKE) clean

