# $TenDRA$

CFLAGS+= -I${.CURDIR}
.PATH : ${.CURDIR}

PROG = tcc

MAN+=	tchk.1 tccenv.5

SRCS=	archive.c compile.c environ.c execute.c filename.c \
	flags.c list.c main.c options.c stages.c startup.c \
	utility.c

.include "${.CURDIR}/../../../mk/base/tendra.prog.mk"
