# $Id$

# Standard directories and files
SRC1=${.CURDIR}/errors

# Standard variables

TCCOPTS=	-Yansi -Xs
CCOPTS=		${TCCOPTS}
LIBS=

# Dependencies and construction rules

PROG=		tld

SRCS=		arg-data.c arg-parse.c bistream.c bostream.c builder.c\
		capsule.c contents.c cstring-list.c cstring.c dalloc.c debug.c\
		dstring.c error-file.c error.c exception.c extract.c\
		file-name.c gen-errors.c istream.c library.c linker.c main.c\
		map-entry.c map-table.c name-entry.c name-key.c name-table.c\
		nstring-list.c ostream.c rename-file.c shape-entry.c\
		shape-table.c syntax.c tdf-read.c tdf-write.c tdf.c\
		unit-entry.c unit-table.c

#ERR_OUT=${SRC}/gen-errors.c ${SRC}/gen-errors.h
#
#EFILES=${SRC1}/arg-data.e ${SRC1}/arg-parse.e ${SRC1}/builder.e\
# ${SRC1}/capsule.e ${SRC1}/contents.e ${SRC1}/error-file.e\
# ${SRC1}/extract.e ${SRC1}/for-osif.e ${SRC1}/library.e ${SRC1}/linker.e\
# ${SRC1}/main.e ${SRC1}/name-entry.e ${SRC1}/rename-file.e\
# ${SRC1}/shape-entry.e ${SRC1}/tdf-read.e
#
#${SRC}/gen-errors.c : ${SRC1}/BUILD_ERRORS ${EFILES}
#	@${REMOVE} ${ERR_OUT}
#	${SRC1}/BUILD_ERRORS -o ${SRC}/gen-errors ${EFILES}

.include "../Makefile.inc"
