# $TenDRA$

TCCFLAGS+=	-f${OBJ_PREFIX}/lib/machines/${BUILD_OS}/${MACH_CPU}/startup/svid3.h

TL=	svid3.tl

SRCS=	acct.c acl.c audit.c cs.c curses.c errno.c eti.c fcntl.c fmtmsg.c \
	form.c ftw.c grp.c ipc.c key_prot.c locale.c lock.c mac.c malloc.c \
	math.c menu.c mman.c mon.c mount.c netconfig.c netdir.c nlist.c \
	panel.c pfmt.c pkginfo.c poll.c priocntl.c priv.c procset.c pwd.c \
	remop.c resource.c rpc.c rpc_types.c rtpriocntl.c shm.c siginfo.c \
	signal.c stat.c statvfs.c stdio.c stdlib.c string.c stropts.c swap.c \
	sys_time.c term.c termio.c termios.c termiox.c time.c timeval.c \
	tiuser.c tspriocntl.c types.c u_old.c ucontext.c uio.c unctrl.c \
	unistd.c ustat.c utmp.c wait.c xdr.c
