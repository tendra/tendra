# $TenDRA$

CFLAGS+= -I${.CURDIR} -I${SRC_DIR}/src/include
.PATH : ${.CURDIR}

PROG = tcc

SRCS=	archive.c compile.c environ.c execute.c filename.c \
	flags.c list.c main.c options.c stages.c startup.c \
	utility.c

.include "${.CURDIR}/../../../mk/base/tendra.prog.mk"
