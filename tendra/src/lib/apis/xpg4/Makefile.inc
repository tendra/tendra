# $TenDRA$

TCCFLAGS+=	-f${OBJ_PREFIX}/lib/machines/${BUILD_OS}/${MACH_CPU}/startup/xpg4.h

TL=	xpg4.tl

SRCS=	iconv.c langinfo.c limits.c monetary.c nl_types.c search.c \
	sem.c shm.c stdio.c time.c unistd.c wchar.c
