# $TenDRA$

.PATH : ${.OBJDIR}/../../unix95.api

TCCFLAGS+=	-f${OBJ_PREFIX}/lib/machines/${SRC_MACHINES}/startup/unix95.h

TL=	unix95.tl

SRCS=	chtype.c curs.c curses.c errno.c fcntl.c fmtmsg.c ftw.c grp.c \
	id_t.c in.c in_t.c inet.c ipc.c libgen.c limits.c math.c mman.c \
	ndbm.c netdb.c poll.c pwd.c re_comp.c resource.c rusage.c sa_famil.c \
	search.c setjmp.c sig.c siginfo_.c signal.c socket.c st_proto.c \
	stat.c statvfs.c stdlib.c string.c strings.c stropts.c sys_time.c \
	syslog.c term.c termios.c time.c timeb.c timeval.c ucontext.c \
	uio.c un.c unctrl.c unistd.c useconds.c utmpx.c wait.c xti.c

.include "../../../../../mk/base/tendra.prog.mk"

