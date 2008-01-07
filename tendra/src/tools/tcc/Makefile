# $TenDRA$

CFLAGS+= -I${.CURDIR} -I${.OBJDIR} -I${SRC_DIR}/src/include
.PATH : ${.CURDIR}

PROG = tcc

SRCS=	archive.c compile.c environ.c execute.c filename.c \
	flags.c list.c main.c options.c stages.c startup.c \
	utility.c

USE_LIBTEN=	yes


.include "${.CURDIR}/../../../mk/base/tendra.prog.mk"
