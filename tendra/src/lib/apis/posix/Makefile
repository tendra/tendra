# $TenDRA$

TCCFLAGS=	-f${OBJ_PREFIX}/lib/machines/${BUILD_OS}/${MACH_CPU}/startup/posix.h

TL=	posix.tl

SRCS=	dirent.c enums.c fcntl.c grp.c limits.c pwd.c setjmp.c signal.c \
	sigset_t.c stdio.c ctuid.c stat.c times.c guid.c ino_t.c mode_t.c \
	off_t.c pid_t.c stat_t.c utsname.c wait.c termios.c time.c \
	getopt.c tcpgrp.c u_old.c u_proto.c utime.c

.include "../Makefile.inc"

.include "${.CURDIR}/../../../../mk/base/tendra.prog.mk"
