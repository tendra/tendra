# $TenDRA$

.PATH : ${.OBJDIR}/../../xpg3.api

TCCFLAGS+=	-f${OBJ_PREFIX}/lib/machines/${SRC_MACHINES}/startup/xpg3.h

TL=	xpg3.tl

SRCS=	ctype.c dirent.c enums.c expg4.c ftw.c ipc.c key_t.c langinfo.c \
	math.c msg.c nl_types.c o_sync.c putenv.c rand48.c s_isvtx.c search.c \
	sem.c sem_prot.c shm.c shm_prot.c srch_pro.c st_proto.c stdio.c \
	string.c termios.c u_plus.c ulimit.c unistd.c values.c xti.c

.include "../../../../../mk/base/tendra.prog.mk"

