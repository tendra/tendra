##  Unix makefile for editline library.
##
##  Set your options:
##	-DANSI_ARROWS		ANSI arrows keys work like emacs.
##	-DHAVE_STDLIB		Have <stdlib.h>.
##	-DHAVE_TCGETATTR	Have tcgetattr(), tcsetattr().
##	-DHAVE_TERMIO		Have "struct termio" and <termio.h>
##	(If neither of above two, we use <sgttyb.h> and BSD ioctl's)
##	-DHIDE			Make static functions static (non debug).
##	-DHIST_SIZE=n		History size.
##	-DNEED_STRDUP		Don't have strdup().
##	-DUNIQUE_HISTORY	Don't save command if same as last one.
##	-DUSE_DIRENT		Use <dirent.h>, not <sys/dir.h>?
##	-DUSE_TERMCAP		Use the termcap library for terminal size
##				see LDFLAGS, below, if you set this.
##	-DNEED_PERROR		Don't have perror() (used in testit)

DEFS	=-DANSI_ARROWS -DHAVE_STDLIB -DHAVE_TCGETATTR -DHIDE -DUSE_DIRENT \
-DHIST_SIZE=100 -DUSE_TERMCAP -DSYS_UNIX -DNEED_STRDUP

CFLAGS	=-O -D_MINIX -D_POSIX_SOURCE $(DEFS)
CC1	=tcc -Ysystem -c $(CFLAGS)

##  If you have -DUSE_TERMCAP, set this as appropriate:
#LDFLAGS = -ltermlib
#LDFLAGS = -ltermcap

##  End of configuration.

SRC=/usr/src/lib/editline
SRC1=${BASE}/src/lib/machines/minix/80x86/src/edit
LIBRARY=$(NAME)

all: $(LIBRARY)

OBJECTS	= $(LIBRARY)(editline.o) $(LIBRARY)(complete.o) $(LIBRARY)(sysunix.o)

$(LIBRARY):	$(OBJECTS)
	aal cr $@ *.o
	rm *.o

$(OBJECTS):	$(SRC)/editline.h

$(LIBRARY)(editline.o):	$(SRC)/editline.c
	$(CC1) -f$(SRC1)/../pragma_fptr.h $(SRC)/editline.c

$(LIBRARY)(complete.o):	$(SRC)/complete.c
	$(CC1) -f$(SRC1)/../pragma_qual.h $(SRC)/complete.c

$(LIBRARY)(sysunix.o):	$(SRC)/sysunix.c
	$(CC1) $(SRC)/sysunix.c
