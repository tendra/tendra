# $TenDRA$

CFLAGS= -I${.CURDIR} -I.
.PATH.c : ${.CURDIR} .

PROG = tld

SRCS=	arg-data.c arg-parse.c bistream.c bostream.c builder.c capsule.c \
	contents.c cstring-list.c cstring.c dalloc.c debug.c dstring.c \
	error-file.c error.c exception.c extract.c file-name.c gen-errors.c \
	istream.c library.c linker.c main.c map-entry.c map-table.c name-entry.c \
	name-key.c name-table.c nstring-list.c ostream.c rename-file.c \
	shape-entry.c shape-table.c syntax.c tdf-read.c tdf-write.c \
	tdf.c unit-entry.c unit-table.c

DEPEND_SRC=	gen-errors.c

ERRORFILES=	arg-data.e arg-parse.e builder.e capsule.e contents.e error-file.e \
		extract.e for-osif.e library.e linker.e main.e name-entry.e \
		rename-file.e shape-entry.e tdf-read.e

gen-errors.c:
	${PERL} -w ${.CURDIR}/errors/BUILD_ERRORS -o ${.OBJDIR}/gen-errors \
	${ERRORFILES:S|^|${.CURDIR}/errors/|}

CLEANFILES+=	gen-errors.c gen-errors.h

.include "${.CURDIR}/../../../mk/base/tendra.prog.mk"
