# $TenDRA$

CFLAGS+= -I${.CURDIR} -I${SRC_DIR}/src/include -I.
.PATH : ${.CURDIR} .

PROG = tld

SRCS=	arg-data.c arg-parse.c bistream.c bostream.c builder.c capsule.c \
	contents.c cstring-list.c dalloc.c debug.c exception.c extract.c \
	file-name.c istream.c library.c linker.c main.c map-entry.c \
	map-table.c name-entry.c \
	name-key.c name-table.c nstring-list.c rename-file.c \
	shape-entry.c shape-table.c syntax.c tdf-read.c tdf-write.c \
	tdf.c unit-entry.c unit-table.c

USE_LIBTEN=	yes

CAT_PRODS=	-n ${.OBJDIR}/catstdn.h

CLEANFILES+=	catstdn.h

.include "${.CURDIR}/../../../mk/base/tendra.prog.mk"
