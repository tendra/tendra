# $TenDRA$

TCCFLAGS+=	-f${OBJ_PREFIX}/lib/machines/${SRC_MACHINES}/startup/iso99.h -Yc99

.PATH : ${.OBJDIR}/../../iso99.api

TL=	iso99.tl

SRCS=	_file.c _ptrdiff.c _sig_ato.c _size_t.c _wchar_t.c _wint_t.c ctype.c \
	errno.c fenv.c float.c limits.c locale.c math.c signal.c stddef.c \
	stdint.c stdio.c stdlib.c string.c time.c va_copy.c wchar.c wchar_ma.c \
	wctype.c wint.c

.include "../../../../../mk/base/tendra.prog.mk"
