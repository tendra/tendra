# Makefile for lib/syscall.

SRC=/usr/src/lib/syscall
LIBRARY=$(NAME)
CC1=tcc -Ysystem -c

all: $(LIBRARY)

OBJECTS	= \
	$(LIBRARY)(_exit.o) \
	$(LIBRARY)(access.o) \
	$(LIBRARY)(alarm.o) \
	$(LIBRARY)(allocmem.o) \
	$(LIBRARY)(freemem.o) \
	$(LIBRARY)(brk.o) \
	$(LIBRARY)(cfgetispeed.o) \
	$(LIBRARY)(cfgetospeed.o) \
	$(LIBRARY)(cfsetispeed.o) \
	$(LIBRARY)(cfsetospeed.o) \
	$(LIBRARY)(chdir.o) \
	$(LIBRARY)(chmod.o) \
	$(LIBRARY)(chown.o) \
	$(LIBRARY)(chroot.o) \
	$(LIBRARY)(close.o) \
	$(LIBRARY)(closedir.o) \
	$(LIBRARY)(creat.o) \
	$(LIBRARY)(devctl.o) \
	$(LIBRARY)(dup.o) \
	$(LIBRARY)(dup2.o) \
	$(LIBRARY)(execl.o) \
	$(LIBRARY)(execle.o) \
	$(LIBRARY)(execlp.o) \
	$(LIBRARY)(execv.o) \
	$(LIBRARY)(execve.o) \
	$(LIBRARY)(execvp.o) \
	$(LIBRARY)(fcntl.o) \
	$(LIBRARY)(fork.o) \
	$(LIBRARY)(fpathconf.o) \
	$(LIBRARY)(fstat.o) \
	$(LIBRARY)(fstatfs.o) \
	$(LIBRARY)(getcwd.o) \
	$(LIBRARY)(getegid.o) \
	$(LIBRARY)(geteuid.o) \
	$(LIBRARY)(getgid.o) \
	$(LIBRARY)(getgroups.o) \
	$(LIBRARY)(getnpid.o) \
	$(LIBRARY)(getnprocnr.o) \
	$(LIBRARY)(getpprocnr.o) \
	$(LIBRARY)(getpgrp.o) \
	$(LIBRARY)(getpid.o) \
	$(LIBRARY)(getppid.o) \
	$(LIBRARY)(getuid.o) \
	$(LIBRARY)(getprocnr.o) \
	$(LIBRARY)(getsysinfo.o) \
	$(LIBRARY)(findproc.o) \
	$(LIBRARY)(ioctl.o) \
	$(LIBRARY)(isatty.o) \
	$(LIBRARY)(kill.o) \
	$(LIBRARY)(link.o) \
	$(LIBRARY)(lseek.o) \
	$(LIBRARY)(mkdir.o) \
	$(LIBRARY)(mkfifo.o) \
	$(LIBRARY)(mknod.o) \
	$(LIBRARY)(mount.o) \
	$(LIBRARY)(open.o) \
	$(LIBRARY)(opendir.o) \
	$(LIBRARY)(pathconf.o) \
	$(LIBRARY)(pause.o) \
	$(LIBRARY)(pipe.o) \
	$(LIBRARY)(ptrace.o) \
	$(LIBRARY)(read.o) \
	$(LIBRARY)(readdir.o) \
	$(LIBRARY)(reboot.o) \
	$(LIBRARY)(rename.o) \
	$(LIBRARY)(rewinddir.o) \
	$(LIBRARY)(rmdir.o) \
	$(LIBRARY)(sbrk.o) \
	$(LIBRARY)(seekdir.o) \
	$(LIBRARY)(setgid.o) \
	$(LIBRARY)(setsid.o) \
	$(LIBRARY)(setuid.o) \
	$(LIBRARY)(sigaction.o) \
	$(LIBRARY)(sigaddset.o) \
	$(LIBRARY)(sigdelset.o) \
	$(LIBRARY)(sigemptyset.o) \
	$(LIBRARY)(sigfillset.o) \
	$(LIBRARY)(sigismember.o) \
	$(LIBRARY)(sigpending.o) \
	$(LIBRARY)(sigprocmask.o) \
	$(LIBRARY)(sigreturn.o) \
	$(LIBRARY)(sigsuspend.o) \
	$(LIBRARY)(sleep.o) \
	$(LIBRARY)(stat.o) \
	$(LIBRARY)(stime.o) \
	$(LIBRARY)(sync.o) \
	$(LIBRARY)(svrctl.o) \
	$(LIBRARY)(tcdrain.o) \
	$(LIBRARY)(tcflow.o) \
	$(LIBRARY)(tcflush.o) \
	$(LIBRARY)(tcgetattr.o) \
	$(LIBRARY)(tcsendbreak.o) \
	$(LIBRARY)(tcsetattr.o) \
	$(LIBRARY)(time.o) \
	$(LIBRARY)(times.o) \
	$(LIBRARY)(umask.o) \
	$(LIBRARY)(umount.o) \
	$(LIBRARY)(uname.o) \
	$(LIBRARY)(unlink.o) \
	$(LIBRARY)(utime.o) \
	$(LIBRARY)(wait.o) \
	$(LIBRARY)(waitpid.o) \
	$(LIBRARY)(write.o) \

$(LIBRARY):	$(OBJECTS)
	aal cr $@ *.o
	rm *.o

$(LIBRARY)(_exit.o):	$(SRC)/_exit.s
	$(CC1) $(SRC)/_exit.s

$(LIBRARY)(access.o):	$(SRC)/access.s
	$(CC1) $(SRC)/access.s

$(LIBRARY)(alarm.o):	$(SRC)/alarm.s
	$(CC1) $(SRC)/alarm.s

$(LIBRARY)(allocmem.o):	$(SRC)/allocmem.s
	$(CC1) $(SRC)/allocmem.s

$(LIBRARY)(freemem.o):	$(SRC)/freemem.s
	$(CC1) $(SRC)/freemem.s

$(LIBRARY)(brk.o):	$(SRC)/brk.s
	$(CC1) $(SRC)/brk.s

$(LIBRARY)(cfgetispeed.o):	$(SRC)/cfgetispeed.s
	$(CC1) $(SRC)/cfgetispeed.s

$(LIBRARY)(cfgetospeed.o):	$(SRC)/cfgetospeed.s
	$(CC1) $(SRC)/cfgetospeed.s

$(LIBRARY)(cfsetispeed.o):	$(SRC)/cfsetispeed.s
	$(CC1) $(SRC)/cfsetispeed.s

$(LIBRARY)(cfsetospeed.o):	$(SRC)/cfsetospeed.s
	$(CC1) $(SRC)/cfsetospeed.s

$(LIBRARY)(chdir.o):	$(SRC)/chdir.s
	$(CC1) $(SRC)/chdir.s

$(LIBRARY)(chmod.o):	$(SRC)/chmod.s
	$(CC1) $(SRC)/chmod.s

$(LIBRARY)(chown.o):	$(SRC)/chown.s
	$(CC1) $(SRC)/chown.s

$(LIBRARY)(chroot.o):	$(SRC)/chroot.s
	$(CC1) $(SRC)/chroot.s

$(LIBRARY)(close.o):	$(SRC)/close.s
	$(CC1) $(SRC)/close.s

$(LIBRARY)(closedir.o):	$(SRC)/closedir.s
	$(CC1) $(SRC)/closedir.s

$(LIBRARY)(creat.o):	$(SRC)/creat.s
	$(CC1) $(SRC)/creat.s

$(LIBRARY)(devctl.o):	$(SRC)/devctl.s
	$(CC1) $(SRC)/devctl.s

$(LIBRARY)(dup.o):	$(SRC)/dup.s
	$(CC1) $(SRC)/dup.s

$(LIBRARY)(dup2.o):	$(SRC)/dup2.s
	$(CC1) $(SRC)/dup2.s

$(LIBRARY)(execl.o):	$(SRC)/execl.s
	$(CC1) $(SRC)/execl.s

$(LIBRARY)(execle.o):	$(SRC)/execle.s
	$(CC1) $(SRC)/execle.s

$(LIBRARY)(execlp.o):	$(SRC)/execlp.s
	$(CC1) $(SRC)/execlp.s

$(LIBRARY)(execv.o):	$(SRC)/execv.s
	$(CC1) $(SRC)/execv.s

$(LIBRARY)(execve.o):	$(SRC)/execve.s
	$(CC1) $(SRC)/execve.s

$(LIBRARY)(execvp.o):	$(SRC)/execvp.s
	$(CC1) $(SRC)/execvp.s

$(LIBRARY)(fcntl.o):	$(SRC)/fcntl.s
	$(CC1) $(SRC)/fcntl.s

$(LIBRARY)(fork.o):	$(SRC)/fork.s
	$(CC1) $(SRC)/fork.s

$(LIBRARY)(fpathconf.o):	$(SRC)/fpathconf.s
	$(CC1) $(SRC)/fpathconf.s

$(LIBRARY)(fstatfs.o):	$(SRC)/fstatfs.s
	$(CC1) $(SRC)/fstatfs.s

$(LIBRARY)(fstat.o):	$(SRC)/fstat.s
	$(CC1) $(SRC)/fstat.s

$(LIBRARY)(getcwd.o):	$(SRC)/getcwd.s
	$(CC1) $(SRC)/getcwd.s

$(LIBRARY)(getegid.o):	$(SRC)/getegid.s
	$(CC1) $(SRC)/getegid.s

$(LIBRARY)(geteuid.o):	$(SRC)/geteuid.s
	$(CC1) $(SRC)/geteuid.s

$(LIBRARY)(getgid.o):	$(SRC)/getgid.s
	$(CC1) $(SRC)/getgid.s

$(LIBRARY)(getgroups.o):	$(SRC)/getgroups.s
	$(CC1) $(SRC)/getgroups.s

$(LIBRARY)(getnpid.o):	$(SRC)/getnpid.s
	$(CC1) $(SRC)/getnpid.s

$(LIBRARY)(getnprocnr.o):	$(SRC)/getnprocnr.s
	$(CC1) $(SRC)/getnprocnr.s

$(LIBRARY)(getpprocnr.o):	$(SRC)/getpprocnr.s
	$(CC1) $(SRC)/getpprocnr.s

$(LIBRARY)(getpgrp.o):	$(SRC)/getpgrp.s
	$(CC1) $(SRC)/getpgrp.s

$(LIBRARY)(getpid.o):	$(SRC)/getpid.s
	$(CC1) $(SRC)/getpid.s

$(LIBRARY)(getppid.o):	$(SRC)/getppid.s
	$(CC1) $(SRC)/getppid.s

$(LIBRARY)(getuid.o):	$(SRC)/getuid.s
	$(CC1) $(SRC)/getuid.s

$(LIBRARY)(getprocnr.o):	$(SRC)/getprocnr.s
	$(CC1) $(SRC)/getprocnr.s

$(LIBRARY)(getsysinfo.o):	$(SRC)/getsysinfo.s
	$(CC1) $(SRC)/getsysinfo.s

$(LIBRARY)(findproc.o):	$(SRC)/findproc.s
	$(CC1) $(SRC)/findproc.s

$(LIBRARY)(ioctl.o):	$(SRC)/ioctl.s
	$(CC1) $(SRC)/ioctl.s

$(LIBRARY)(isatty.o):	$(SRC)/isatty.s
	$(CC1) $(SRC)/isatty.s

$(LIBRARY)(kill.o):	$(SRC)/kill.s
	$(CC1) $(SRC)/kill.s

$(LIBRARY)(link.o):	$(SRC)/link.s
	$(CC1) $(SRC)/link.s

$(LIBRARY)(lseek.o):	$(SRC)/lseek.s
	$(CC1) $(SRC)/lseek.s

$(LIBRARY)(mkdir.o):	$(SRC)/mkdir.s
	$(CC1) $(SRC)/mkdir.s

$(LIBRARY)(mkfifo.o):	$(SRC)/mkfifo.s
	$(CC1) $(SRC)/mkfifo.s

$(LIBRARY)(mknod.o):	$(SRC)/mknod.s
	$(CC1) $(SRC)/mknod.s

$(LIBRARY)(mount.o):	$(SRC)/mount.s
	$(CC1) $(SRC)/mount.s

$(LIBRARY)(open.o):	$(SRC)/open.s
	$(CC1) $(SRC)/open.s

$(LIBRARY)(opendir.o):	$(SRC)/opendir.s
	$(CC1) $(SRC)/opendir.s

$(LIBRARY)(pathconf.o):	$(SRC)/pathconf.s
	$(CC1) $(SRC)/pathconf.s

$(LIBRARY)(pause.o):	$(SRC)/pause.s
	$(CC1) $(SRC)/pause.s

$(LIBRARY)(pipe.o):	$(SRC)/pipe.s
	$(CC1) $(SRC)/pipe.s

$(LIBRARY)(ptrace.o):	$(SRC)/ptrace.s
	$(CC1) $(SRC)/ptrace.s

$(LIBRARY)(read.o):	$(SRC)/read.s
	$(CC1) $(SRC)/read.s

$(LIBRARY)(readdir.o):	$(SRC)/readdir.s
	$(CC1) $(SRC)/readdir.s

$(LIBRARY)(reboot.o):	$(SRC)/reboot.s
	$(CC1) $(SRC)/reboot.s

$(LIBRARY)(rename.o):	$(SRC)/rename.s
	$(CC1) $(SRC)/rename.s

$(LIBRARY)(rewinddir.o):	$(SRC)/rewinddir.s
	$(CC1) $(SRC)/rewinddir.s

$(LIBRARY)(rmdir.o):	$(SRC)/rmdir.s
	$(CC1) $(SRC)/rmdir.s

$(LIBRARY)(sbrk.o):	$(SRC)/sbrk.s
	$(CC1) $(SRC)/sbrk.s

$(LIBRARY)(seekdir.o):	$(SRC)/seekdir.s
	$(CC1) $(SRC)/seekdir.s

$(LIBRARY)(setgid.o):	$(SRC)/setgid.s
	$(CC1) $(SRC)/setgid.s

$(LIBRARY)(setsid.o):	$(SRC)/setsid.s
	$(CC1) $(SRC)/setsid.s

$(LIBRARY)(setuid.o):	$(SRC)/setuid.s
	$(CC1) $(SRC)/setuid.s

$(LIBRARY)(sigaction.o):	$(SRC)/sigaction.s
	$(CC1) $(SRC)/sigaction.s

$(LIBRARY)(sigaddset.o):	$(SRC)/sigaddset.s
	$(CC1) $(SRC)/sigaddset.s

$(LIBRARY)(sigdelset.o):	$(SRC)/sigdelset.s
	$(CC1) $(SRC)/sigdelset.s

$(LIBRARY)(sigemptyset.o):	$(SRC)/sigemptyset.s
	$(CC1) $(SRC)/sigemptyset.s

$(LIBRARY)(sigfillset.o):	$(SRC)/sigfillset.s
	$(CC1) $(SRC)/sigfillset.s

$(LIBRARY)(sigismember.o):	$(SRC)/sigismember.s
	$(CC1) $(SRC)/sigismember.s

$(LIBRARY)(sigpending.o):	$(SRC)/sigpending.s
	$(CC1) $(SRC)/sigpending.s

$(LIBRARY)(sigprocmask.o):	$(SRC)/sigprocmask.s
	$(CC1) $(SRC)/sigprocmask.s

$(LIBRARY)(sigreturn.o):	$(SRC)/sigreturn.s
	$(CC1) $(SRC)/sigreturn.s

$(LIBRARY)(sigsuspend.o):	$(SRC)/sigsuspend.s
	$(CC1) $(SRC)/sigsuspend.s

$(LIBRARY)(sleep.o):	$(SRC)/sleep.s
	$(CC1) $(SRC)/sleep.s

$(LIBRARY)(stat.o):	$(SRC)/stat.s
	$(CC1) $(SRC)/stat.s

$(LIBRARY)(stime.o):	$(SRC)/stime.s
	$(CC1) $(SRC)/stime.s

$(LIBRARY)(sync.o):	$(SRC)/sync.s
	$(CC1) $(SRC)/sync.s

$(LIBRARY)(svrctl.o):	$(SRC)/svrctl.s
	$(CC1) $(SRC)/svrctl.s

$(LIBRARY)(tcdrain.o):	$(SRC)/tcdrain.s
	$(CC1) $(SRC)/tcdrain.s

$(LIBRARY)(tcflow.o):	$(SRC)/tcflow.s
	$(CC1) $(SRC)/tcflow.s

$(LIBRARY)(tcflush.o):	$(SRC)/tcflush.s
	$(CC1) $(SRC)/tcflush.s

$(LIBRARY)(tcgetattr.o):	$(SRC)/tcgetattr.s
	$(CC1) $(SRC)/tcgetattr.s

$(LIBRARY)(tcsendbreak.o):	$(SRC)/tcsendbreak.s
	$(CC1) $(SRC)/tcsendbreak.s

$(LIBRARY)(tcsetattr.o):	$(SRC)/tcsetattr.s
	$(CC1) $(SRC)/tcsetattr.s

$(LIBRARY)(time.o):	$(SRC)/time.s
	$(CC1) $(SRC)/time.s

$(LIBRARY)(times.o):	$(SRC)/times.s
	$(CC1) $(SRC)/times.s

$(LIBRARY)(umask.o):	$(SRC)/umask.s
	$(CC1) $(SRC)/umask.s

$(LIBRARY)(umount.o):	$(SRC)/umount.s
	$(CC1) $(SRC)/umount.s

$(LIBRARY)(uname.o):	$(SRC)/uname.s
	$(CC1) $(SRC)/uname.s

$(LIBRARY)(unlink.o):	$(SRC)/unlink.s
	$(CC1) $(SRC)/unlink.s

$(LIBRARY)(utime.o):	$(SRC)/utime.s
	$(CC1) $(SRC)/utime.s

$(LIBRARY)(wait.o):	$(SRC)/wait.s
	$(CC1) $(SRC)/wait.s

$(LIBRARY)(waitpid.o):	$(SRC)/waitpid.s
	$(CC1) $(SRC)/waitpid.s

$(LIBRARY)(write.o):	$(SRC)/write.s
	$(CC1) $(SRC)/write.s
