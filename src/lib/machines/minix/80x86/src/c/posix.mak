# Makefile for lib/posix.

SRC=/usr/src/lib/posix
LIBRARY=$(NAME)
CC1=tcc -Ysystem -c -I$(SRC)

all: $(LIBRARY)

OBJECTS	= \
	$(LIBRARY)(__exit.o) \
	$(LIBRARY)(_access.o) \
	$(LIBRARY)(_alarm.o) \
	$(LIBRARY)(_cfgetispeed.o) \
	$(LIBRARY)(_cfgetospeed.o) \
	$(LIBRARY)(_cfsetispeed.o) \
	$(LIBRARY)(_cfsetospeed.o) \
	$(LIBRARY)(_chdir.o) \
	$(LIBRARY)(_chmod.o) \
	$(LIBRARY)(_chown.o) \
	$(LIBRARY)(_chroot.o) \
	$(LIBRARY)(_close.o) \
	$(LIBRARY)(_closedir.o) \
	$(LIBRARY)(_creat.o) \
	$(LIBRARY)(_dup.o) \
	$(LIBRARY)(_dup2.o) \
	$(LIBRARY)(_exec.o) \
	$(LIBRARY)(_execn.o) \
	$(LIBRARY)(_fcntl.o) \
	$(LIBRARY)(_fork.o) \
	$(LIBRARY)(_fpathconf.o) \
	$(LIBRARY)(_fstat.o) \
	$(LIBRARY)(_getcwd.o) \
	$(LIBRARY)(_getegid.o) \
	$(LIBRARY)(_geteuid.o) \
	$(LIBRARY)(_getgid.o) \
	$(LIBRARY)(_getgroups.o) \
	$(LIBRARY)(_getpgrp.o) \
	$(LIBRARY)(_getpid.o) \
	$(LIBRARY)(_getppid.o) \
	$(LIBRARY)(_getuid.o) \
	$(LIBRARY)(_ioctl.o) \
	$(LIBRARY)(_isatty.o) \
	$(LIBRARY)(_kill.o) \
	$(LIBRARY)(_link.o) \
	$(LIBRARY)(_lseek.o) \
	$(LIBRARY)(_mkdir.o) \
	$(LIBRARY)(_mkfifo.o) \
	$(LIBRARY)(_mknod.o) \
	$(LIBRARY)(_mktemp.o) \
	$(LIBRARY)(_mount.o) \
	$(LIBRARY)(_open.o) \
	$(LIBRARY)(_opendir.o) \
	$(LIBRARY)(_pathconf.o) \
	$(LIBRARY)(_pause.o) \
	$(LIBRARY)(_pipe.o) \
	$(LIBRARY)(_ptrace.o) \
	$(LIBRARY)(_read.o) \
	$(LIBRARY)(_readdir.o) \
	$(LIBRARY)(_rename.o) \
	$(LIBRARY)(_rewinddir.o) \
	$(LIBRARY)(_rmdir.o) \
	$(LIBRARY)(_setgid.o) \
	$(LIBRARY)(_setsid.o) \
	$(LIBRARY)(_setuid.o) \
	$(LIBRARY)(_sigaction.o) \
	$(LIBRARY)(_sigpending.o) \
	$(LIBRARY)(_sigprocmask.o) \
	$(LIBRARY)(_sigreturn.o) \
	$(LIBRARY)(_sigset.o) \
	$(LIBRARY)(_sigsuspend.o) \
	$(LIBRARY)(_sleep.o) \
	$(LIBRARY)(_stat.o) \
	$(LIBRARY)(_stime.o) \
	$(LIBRARY)(_sync.o) \
	$(LIBRARY)(_tcdrain.o) \
	$(LIBRARY)(_tcflow.o) \
	$(LIBRARY)(_tcflush.o) \
	$(LIBRARY)(_tcgetattr.o) \
	$(LIBRARY)(_tcsendbreak.o) \
	$(LIBRARY)(_tcsetattr.o) \
	$(LIBRARY)(_time.o) \
	$(LIBRARY)(_times.o) \
	$(LIBRARY)(_umask.o) \
	$(LIBRARY)(_umount.o) \
	$(LIBRARY)(_uname.o) \
	$(LIBRARY)(_unlink.o) \
	$(LIBRARY)(_utime.o) \
	$(LIBRARY)(_wait.o) \
	$(LIBRARY)(_waitpid.o) \
	$(LIBRARY)(_write.o) \

$(LIBRARY):	$(OBJECTS)
	aal cr $@ *.o
	rm *.o

$(LIBRARY)(__exit.o):	$(SRC)/__exit.c
	$(CC1) $(SRC)/__exit.c

$(LIBRARY)(_access.o):	$(SRC)/_access.c
	$(CC1) $(SRC)/_access.c

$(LIBRARY)(_alarm.o):	$(SRC)/_alarm.c
	$(CC1) $(SRC)/_alarm.c

$(LIBRARY)(_cfgetispeed.o):	$(SRC)/_cfgetispeed.c
	$(CC1) $(SRC)/_cfgetispeed.c

$(LIBRARY)(_cfgetospeed.o):	$(SRC)/_cfgetospeed.c
	$(CC1) $(SRC)/_cfgetospeed.c

$(LIBRARY)(_cfsetispeed.o):	$(SRC)/_cfsetispeed.c
	$(CC1) $(SRC)/_cfsetispeed.c

$(LIBRARY)(_cfsetospeed.o):	$(SRC)/_cfsetospeed.c
	$(CC1) $(SRC)/_cfsetospeed.c

$(LIBRARY)(_chdir.o):	$(SRC)/_chdir.c
	$(CC1) $(SRC)/_chdir.c

$(LIBRARY)(_chmod.o):	$(SRC)/_chmod.c
	$(CC1) $(SRC)/_chmod.c

$(LIBRARY)(_chown.o):	$(SRC)/_chown.c
	$(CC1) $(SRC)/_chown.c

$(LIBRARY)(_chroot.o):	$(SRC)/_chroot.c
	$(CC1) $(SRC)/_chroot.c

$(LIBRARY)(_close.o):	$(SRC)/_close.c
	$(CC1) $(SRC)/_close.c

$(LIBRARY)(_closedir.o):	$(SRC)/_closedir.c
	$(CC1) $(SRC)/_closedir.c

$(LIBRARY)(_creat.o):	$(SRC)/_creat.c
	$(CC1) $(SRC)/_creat.c

$(LIBRARY)(_dup.o):	$(SRC)/_dup.c
	$(CC1) $(SRC)/_dup.c

$(LIBRARY)(_dup2.o):	$(SRC)/_dup2.c
	$(CC1) $(SRC)/_dup2.c

$(LIBRARY)(_exec.o):	$(SRC)/_exec.c
	$(CC1) $(SRC)/_exec.c

$(LIBRARY)(_execn.o):	$(SRC)/_execn.c
	$(CC1) $(SRC)/_execn.c

$(LIBRARY)(_fcntl.o):	$(SRC)/_fcntl.c
	$(CC1) $(SRC)/_fcntl.c

$(LIBRARY)(_fork.o):	$(SRC)/_fork.c
	$(CC1) $(SRC)/_fork.c

$(LIBRARY)(_fpathconf.o):	$(SRC)/_fpathconf.c
	$(CC1) $(SRC)/_fpathconf.c

$(LIBRARY)(_fstat.o):	$(SRC)/_fstat.c
	$(CC1) $(SRC)/_fstat.c

$(LIBRARY)(_getcwd.o):	$(SRC)/_getcwd.c
	$(CC1) $(SRC)/_getcwd.c

$(LIBRARY)(_getegid.o):	$(SRC)/_getegid.c
	$(CC1) $(SRC)/_getegid.c

$(LIBRARY)(_geteuid.o):	$(SRC)/_geteuid.c
	$(CC1) $(SRC)/_geteuid.c

$(LIBRARY)(_getgid.o):	$(SRC)/_getgid.c
	$(CC1) $(SRC)/_getgid.c

$(LIBRARY)(_getgroups.o):	$(SRC)/_getgroups.c
	$(CC1) $(SRC)/_getgroups.c

$(LIBRARY)(_getpgrp.o):	$(SRC)/_getpgrp.c
	$(CC1) $(SRC)/_getpgrp.c

$(LIBRARY)(_getpid.o):	$(SRC)/_getpid.c
	$(CC1) $(SRC)/_getpid.c

$(LIBRARY)(_getppid.o):	$(SRC)/_getppid.c
	$(CC1) $(SRC)/_getppid.c

$(LIBRARY)(_getuid.o):	$(SRC)/_getuid.c
	$(CC1) $(SRC)/_getuid.c

$(LIBRARY)(_ioctl.o):	$(SRC)/_ioctl.c
	$(CC1) $(SRC)/_ioctl.c

$(LIBRARY)(_isatty.o):	$(SRC)/_isatty.c
	$(CC1) $(SRC)/_isatty.c

$(LIBRARY)(_kill.o):	$(SRC)/_kill.c
	$(CC1) $(SRC)/_kill.c

$(LIBRARY)(_link.o):	$(SRC)/_link.c
	$(CC1) $(SRC)/_link.c

$(LIBRARY)(_lseek.o):	$(SRC)/_lseek.c
	$(CC1) $(SRC)/_lseek.c

$(LIBRARY)(_mkdir.o):	$(SRC)/_mkdir.c
	$(CC1) $(SRC)/_mkdir.c

$(LIBRARY)(_mkfifo.o):	$(SRC)/_mkfifo.c
	$(CC1) $(SRC)/_mkfifo.c

$(LIBRARY)(_mknod.o):	$(SRC)/_mknod.c
	$(CC1) $(SRC)/_mknod.c

$(LIBRARY)(_mktemp.o):	$(SRC)/_mktemp.c
	$(CC1) $(SRC)/_mktemp.c

$(LIBRARY)(_mount.o):	$(SRC)/_mount.c
	$(CC1) $(SRC)/_mount.c

$(LIBRARY)(_open.o):	$(SRC)/_open.c
	$(CC1) $(SRC)/_open.c

$(LIBRARY)(_opendir.o):	$(SRC)/_opendir.c
	$(CC1) $(SRC)/_opendir.c

$(LIBRARY)(_pathconf.o):	$(SRC)/_pathconf.c
	$(CC1) $(SRC)/_pathconf.c

$(LIBRARY)(_pause.o):	$(SRC)/_pause.c
	$(CC1) $(SRC)/_pause.c

$(LIBRARY)(_pipe.o):	$(SRC)/_pipe.c
	$(CC1) $(SRC)/_pipe.c

$(LIBRARY)(_ptrace.o):	$(SRC)/_ptrace.c
	$(CC1) $(SRC)/_ptrace.c

$(LIBRARY)(_read.o):	$(SRC)/_read.c
	$(CC1) $(SRC)/_read.c

$(LIBRARY)(_readdir.o):	$(SRC)/_readdir.c
	$(CC1) $(SRC)/_readdir.c

$(LIBRARY)(_rename.o):	$(SRC)/_rename.c
	$(CC1) $(SRC)/_rename.c

$(LIBRARY)(_rewinddir.o):	$(SRC)/_rewinddir.c
	$(CC1) $(SRC)/_rewinddir.c

$(LIBRARY)(_rmdir.o):	$(SRC)/_rmdir.c
	$(CC1) $(SRC)/_rmdir.c

$(LIBRARY)(_setgid.o):	$(SRC)/_setgid.c
	$(CC1) $(SRC)/_setgid.c

$(LIBRARY)(_setsid.o):	$(SRC)/_setsid.c
	$(CC1) $(SRC)/_setsid.c

$(LIBRARY)(_setuid.o):	$(SRC)/_setuid.c
	$(CC1) $(SRC)/_setuid.c

$(LIBRARY)(_sigaction.o):	$(SRC1)/_sigaction.c
	$(CC1) $(SRC1)/_sigaction.c

$(LIBRARY)(_sigpending.o):	$(SRC)/_sigpending.c
	$(CC1) $(SRC)/_sigpending.c

$(LIBRARY)(_sigprocmask.o):	$(SRC)/_sigprocmask.c
	$(CC1) $(SRC)/_sigprocmask.c

$(LIBRARY)(_sigreturn.o):	$(SRC)/_sigreturn.c
	$(CC1) -D_SETJMP_SAVES_REGS=1 $(SRC)/_sigreturn.c

$(LIBRARY)(_sigset.o):	$(SRC)/_sigset.c
	$(CC1) $(SRC)/_sigset.c

$(LIBRARY)(_sigsuspend.o):	$(SRC)/_sigsuspend.c
	$(CC1) $(SRC)/_sigsuspend.c

$(LIBRARY)(_sleep.o):	$(SRC)/_sleep.c
	$(CC1) $(SRC)/_sleep.c

$(LIBRARY)(_stat.o):	$(SRC)/_stat.c
	$(CC1) $(SRC)/_stat.c

$(LIBRARY)(_stime.o):	$(SRC)/_stime.c
	$(CC1) $(SRC)/_stime.c

$(LIBRARY)(_sync.o):	$(SRC)/_sync.c
	$(CC1) $(SRC)/_sync.c

$(LIBRARY)(_tcdrain.o):	$(SRC)/_tcdrain.c
	$(CC1) $(SRC)/_tcdrain.c

$(LIBRARY)(_tcflow.o):	$(SRC)/_tcflow.c
	$(CC1) $(SRC)/_tcflow.c

$(LIBRARY)(_tcflush.o):	$(SRC)/_tcflush.c
	$(CC1) $(SRC)/_tcflush.c

$(LIBRARY)(_tcgetattr.o):	$(SRC)/_tcgetattr.c
	$(CC1) $(SRC)/_tcgetattr.c

$(LIBRARY)(_tcsendbreak.o):	$(SRC)/_tcsendbreak.c
	$(CC1) $(SRC)/_tcsendbreak.c

$(LIBRARY)(_tcsetattr.o):	$(SRC)/_tcsetattr.c
	$(CC1) $(SRC)/_tcsetattr.c

$(LIBRARY)(_time.o):	$(SRC)/_time.c
	$(CC1) $(SRC)/_time.c

$(LIBRARY)(_times.o):	$(SRC)/_times.c
	$(CC1) $(SRC)/_times.c

$(LIBRARY)(_umask.o):	$(SRC)/_umask.c
	$(CC1) $(SRC)/_umask.c

$(LIBRARY)(_umount.o):	$(SRC)/_umount.c
	$(CC1) $(SRC)/_umount.c

$(LIBRARY)(_uname.o):	$(SRC)/_uname.c /usr/include/minix/config.h
	$(CC1) $(SRC)/_uname.c

$(LIBRARY)(_unlink.o):	$(SRC)/_unlink.c
	$(CC1) $(SRC)/_unlink.c

$(LIBRARY)(_utime.o):	$(SRC)/_utime.c
	$(CC1) $(SRC)/_utime.c

$(LIBRARY)(_wait.o):	$(SRC)/_wait.c
	$(CC1) $(SRC)/_wait.c

$(LIBRARY)(_waitpid.o):	$(SRC)/_waitpid.c
	$(CC1) $(SRC)/_waitpid.c

$(LIBRARY)(_write.o):	$(SRC)/_write.c
	$(CC1) $(SRC)/_write.c
