# $TenDRA$

.PATH : ${.OBJDIR}/../../ansi.api

TCCFLAGS+=       -f${OBJ_PREFIX}/lib/machines/${SRC_MACHINES}/startup/ansi.h

TL=	ansi.tl

SRCS=	alloc.c clock_t.c ctype.c enums.c eof.c errno.c fail.c \
	file.c float.c free.c limits.c locale.c math.c rename.c \
	seek_con.c setjmp.c signal.c size_t.c stddef.c stdio.c \
	stdlib.c string.c sys.c system.c time.c time_t.c tmp_max.c \
	va_args.c va_list.c wchar_t.c xpg3_ran.c xpg4_ran.c


# Build in lib/sys
LDADD?=	../../../sys/sys.j

.include "../../../../../mk/base/tendra.prog.mk"
