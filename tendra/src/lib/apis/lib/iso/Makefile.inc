# $TenDRA$

TCCFLAGS+=	-f${OBJ_PREFIX}/lib/machines/${SRC_MACHINES}/startup/iso.h

.PATH : ${.OBJDIR}/../../iso.api

TL=	iso.tl

SRCS=	errno.c mse.c mse2.c wchar.c wctype.c wint.c

.include "../../../../../mk/base/tendra.prog.mk"

