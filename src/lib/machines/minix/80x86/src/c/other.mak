# Makefile for lib/other.

# The bxxx(), and *index() functions are not used, because they have assembly
# equivalents.

SRC=/usr/src/lib/other
LIBRARY=$(NAME)
CC1=tcc -Ysystem -c -I$(SRC) -I/usr/src

all: $(LIBRARY)

OBJECTS	= \
	$(LIBRARY)(_brk.o) \
	$(LIBRARY)(_reboot.o) \
	$(LIBRARY)(_seekdir.o) \
	$(LIBRARY)(asynchio.o) \
	$(LIBRARY)(crypt.o) \
	$(LIBRARY)(ctermid.o) \
	$(LIBRARY)(cuserid.o) \
	$(LIBRARY)(environ.o) \
	$(LIBRARY)(errno.o) \
	$(LIBRARY)(execlp.o) \
	$(LIBRARY)(fdopen.o) \
	$(LIBRARY)(ffs.o) \
	$(LIBRARY)(fslib.o) \
	$(LIBRARY)(fsversion.o) \
	$(LIBRARY)(getgrent.o) \
	$(LIBRARY)(getlogin.o) \
	$(LIBRARY)(getopt.o) \
	$(LIBRARY)(getpass.o) \
	$(LIBRARY)(getpwent.o) \
	$(LIBRARY)(getttyent.o) \
	$(LIBRARY)(getw.o) \
	$(LIBRARY)(hypot.o) \
	$(LIBRARY)(itoa.o) \
	$(LIBRARY)(loadname.o) \
	$(LIBRARY)(lock.o) \
	$(LIBRARY)(lrand.o) \
	$(LIBRARY)(lsearch.o) \
	$(LIBRARY)(memccpy.o) \
	$(LIBRARY)(mtab.o) \
	$(LIBRARY)(nlist.o) \
	$(LIBRARY)(peekpoke.o) \
	$(LIBRARY)(popen.o) \
	$(LIBRARY)(printk.o) \
	$(LIBRARY)(putenv.o) \
	$(LIBRARY)(putw.o) \
	$(LIBRARY)(regexp.o) \
	$(LIBRARY)(regsub.o) \
	$(LIBRARY)(stderr.o) \
	$(LIBRARY)(swab.o) \
	$(LIBRARY)(syscall.o) \
	$(LIBRARY)(sysconf.o) \
	$(LIBRARY)(telldir.o) \
	$(LIBRARY)(termcap.o) \
	$(LIBRARY)(ttyname.o) \
	$(LIBRARY)(ttyslot.o) \

$(LIBRARY):	$(OBJECTS)
	aal cr $@ *.o
	rm *.o

$(LIBRARY)(_brk.o):	$(SRC)/_brk.c
	$(CC1) $(SRC)/_brk.c

$(LIBRARY)(_reboot.o):	$(SRC)/_reboot.c
	$(CC1) $(SRC)/_reboot.c

$(LIBRARY)(_seekdir.o):	$(SRC)/_seekdir.c
	$(CC1) $(SRC)/_seekdir.c

$(LIBRARY)(asynchio.o):	$(SRC)/asynchio.c
	$(CC1) $(SRC)/asynchio.c

$(LIBRARY)(bcmp.o):	$(SRC)/bcmp.c
	$(CC1) $(SRC)/bcmp.c

$(LIBRARY)(bcopy.o):	$(SRC)/bcopy.c
	$(CC1) $(SRC)/bcopy.c

$(LIBRARY)(bzero.o):	$(SRC)/bzero.c
	$(CC1) $(SRC)/bzero.c

$(LIBRARY)(crypt.o):	$(SRC)/crypt.c
	$(CC1) $(SRC)/crypt.c

$(LIBRARY)(ctermid.o):	$(SRC)/ctermid.c
	$(CC1) $(SRC)/ctermid.c

$(LIBRARY)(cuserid.o):	$(SRC)/cuserid.c
	$(CC1) $(SRC)/cuserid.c

$(LIBRARY)(environ.o):	$(SRC)/environ.c
	$(CC1) $(SRC)/environ.c

$(LIBRARY)(errno.o):	$(SRC)/errno.c
	$(CC1) $(SRC)/errno.c

$(LIBRARY)(execlp.o):	$(SRC)/execlp.c
	$(CC1) $(SRC)/execlp.c

$(LIBRARY)(fdopen.o):	$(SRC)/fdopen.c
	$(CC1) $(SRC)/fdopen.c

$(LIBRARY)(ffs.o):	$(SRC)/ffs.c
	$(CC1) $(SRC)/ffs.c

$(LIBRARY)(fslib.o):	$(SRC)/fslib.c
	$(CC1) $(SRC)/fslib.c

$(LIBRARY)(fsversion.o):	$(SRC)/fsversion.c
	$(CC1) $(SRC)/fsversion.c

$(LIBRARY)(getgrent.o):	$(SRC)/getgrent.c
	$(CC1) $(SRC)/getgrent.c

$(LIBRARY)(getlogin.o):	$(SRC)/getlogin.c
	$(CC1) $(SRC)/getlogin.c

$(LIBRARY)(getopt.o):	$(SRC)/getopt.c
	$(CC1) $(SRC)/getopt.c

$(LIBRARY)(getpass.o):	$(SRC)/getpass.c
	$(CC1) $(SRC)/getpass.c

$(LIBRARY)(getpwent.o):	$(SRC)/getpwent.c
	$(CC1) $(SRC)/getpwent.c

$(LIBRARY)(getttyent.o):	$(SRC)/getttyent.c
	$(CC1) $(SRC)/getttyent.c

$(LIBRARY)(getw.o):	$(SRC)/getw.c
	$(CC1) $(SRC)/getw.c

$(LIBRARY)(hypot.o):	$(SRC)/hypot.c
	$(CC1) $(SRC)/hypot.c

$(LIBRARY)(index.o):	$(SRC)/index.c
	$(CC1) $(SRC)/index.c

$(LIBRARY)(itoa.o):	$(SRC)/itoa.c
	$(CC1) $(SRC)/itoa.c

$(LIBRARY)(loadname.o):	$(SRC)/loadname.c
	$(CC1) $(SRC)/loadname.c

$(LIBRARY)(lock.o):	$(SRC)/lock.c
	$(CC1) $(SRC)/lock.c

$(LIBRARY)(lrand.o):	$(SRC)/lrand.c
	$(CC1) $(SRC)/lrand.c

$(LIBRARY)(lsearch.o):	$(SRC)/lsearch.c
	$(CC1) $(SRC)/lsearch.c

$(LIBRARY)(memccpy.o):	$(SRC)/memccpy.c
	$(CC1) $(SRC)/memccpy.c

$(LIBRARY)(mtab.o):	$(SRC)/mtab.c
	$(CC1) $(SRC)/mtab.c

$(LIBRARY)(nlist.o):	$(SRC)/nlist.c
	$(CC1) $(SRC)/nlist.c

$(LIBRARY)(peekpoke.o):	$(SRC)/peekpoke.c
	$(CC1) $(SRC)/peekpoke.c

$(LIBRARY)(popen.o):	$(SRC)/popen.c
	$(CC1) $(SRC)/popen.c

$(LIBRARY)(printk.o):	$(SRC)/printk.c
	$(CC1) $(SRC)/printk.c

$(LIBRARY)(putenv.o):	$(SRC)/putenv.c
	$(CC1) $(SRC)/putenv.c

$(LIBRARY)(putw.o):	$(SRC)/putw.c
	$(CC1) $(SRC)/putw.c

$(LIBRARY)(regexp.o):	$(SRC)/regexp.c
	$(CC1) $(SRC)/regexp.c

$(LIBRARY)(regsub.o):	$(SRC)/regsub.c
	$(CC1) $(SRC)/regsub.c

$(LIBRARY)(rindex.o):	$(SRC)/rindex.c
	$(CC1) $(SRC)/rindex.c

$(LIBRARY)(stderr.o):	$(SRC)/stderr.c
	$(CC1) $(SRC)/stderr.c

$(LIBRARY)(swab.o):	$(SRC)/swab.c
	$(CC1) $(SRC)/swab.c

$(LIBRARY)(syscall.o):	$(SRC)/syscall.c
	$(CC1) $(SRC)/syscall.c

$(LIBRARY)(sysconf.o):	$(SRC)/sysconf.c
	$(CC1) $(SRC)/sysconf.c

$(LIBRARY)(syslib.o):	$(SRC)/syslib.c
	$(CC1) $(SRC)/syslib.c

$(LIBRARY)(telldir.o):	$(SRC)/telldir.c
	$(CC1) $(SRC)/telldir.c

$(LIBRARY)(termcap.o):	$(SRC)/termcap.c
	$(CC1) $(SRC)/termcap.c

$(LIBRARY)(ttyname.o):	$(SRC)/ttyname.c
	$(CC1) $(SRC)/ttyname.c

$(LIBRARY)(ttyslot.o):	$(SRC)/ttyslot.c
	$(CC1) $(SRC)/ttyslot.c
