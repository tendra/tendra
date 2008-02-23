# $Id$

SRC1=${.CURDIR}/errors

BUILD_ERRORS = errors/BUILD_ERRORS
REMOVE = rm -f

TCCOPTS=	-Yansi -Xs
CCOPTS=		${TCCOPTS} -I${BASE_DIR}/${INCLUDE} -I${.CURDIR} -I${OBJ_SDIR}
LIBS=

PROG=		${.CURDIR:T}

OBJS=		gen-errors.o\
		arg-data.o arg-parse.o bistream.o bostream.o builder.o\
		capsule.o contents.o cstring-list.o cstring.o dalloc.o debug.o\
		dstring.o error.o exception.o extract.o\
		file-name.o istream.o library.o linker.o main.o\
		map-entry.o map-table.o name-entry.o name-key.o name-table.o\
		nstring-list.o ostream.o rename-file.o shape-entry.o\
		shape-table.o syntax.o tdf-read.o tdf-write.o tdf.o\
		unit-entry.o unit-table.o

ERR_OUT=gen-errors.c gen-errors.h

EFILES=${SRC1}/arg-data.e ${SRC1}/arg-parse.e ${SRC1}/builder.e\
 ${SRC1}/capsule.e ${SRC1}/contents.e \
 ${SRC1}/extract.e ${SRC1}/for-osif.e ${SRC1}/library.e ${SRC1}/linker.e\
 ${SRC1}/main.e ${SRC1}/name-entry.e ${SRC1}/rename-file.e\
 ${SRC1}/shape-entry.e ${SRC1}/tdf-read.e

tld: ${OBJS}
	${CC} -o tld ${OBJS}

gen-errors.c : ${BUILD_ERRORS} ${EFILES}
	${REMOVE} ${ERR_OUT};\
	${BUILD_ERRORS} -o gen-errors ${EFILES}

