# Makefile for lib/sysutil.

SRC=/usr/src/lib/sysutil
SRC1=${BASE}/src/lib/machines/minix/80x86/src/sys
LIBRARY=$(NAME)
CC1=tcc -Ysystem -c -I$(SRC)

all: $(LIBRARY)

OBJECTS	= \
	$(LIBRARY)(kmalloc.o) \
	$(LIBRARY)(kprintf.o) \
	$(LIBRARY)(kputc.o) \
	$(LIBRARY)(tickdelay.o) \
	$(LIBRARY)(getuptime.o) \
	$(LIBRARY)(env_get_prm.o) \
	$(LIBRARY)(env_parse.o) \
	$(LIBRARY)(env_panic.o) \
	$(LIBRARY)(env_prefix.o) \
	$(LIBRARY)(fkey_ctl.o) \
	$(LIBRARY)(panic.o) \
	$(LIBRARY)(report.o) \
	$(LIBRARY)(taskcall.o) \

$(LIBRARY):	$(OBJECTS)
	aal cr $@ *.o
	rm *.o

$(LIBRARY)(kmalloc.o):	$(SRC1)/kmalloc.c
	$(CC1) $(SRC1)/kmalloc.c

$(LIBRARY)(kprintf.o):	$(SRC)/kprintf.c
	$(CC1) $(SRC)/kprintf.c

$(LIBRARY)(kputc.o):	$(SRC)/kputc.c
	$(CC1) $(SRC)/kputc.c

$(LIBRARY)(tickdelay.o):	$(SRC)/tickdelay.c
	$(CC1) $(SRC)/tickdelay.c

$(LIBRARY)(getuptime.o):	$(SRC)/getuptime.c
	$(CC1) $(SRC)/getuptime.c

$(LIBRARY)(env_get_prm.o):	$(SRC)/env_get_prm.c
	$(CC1) $(SRC)/env_get_prm.c

$(LIBRARY)(env_parse.o):	$(SRC)/env_parse.c
	$(CC1) $(SRC)/env_parse.c

$(LIBRARY)(env_panic.o):	$(SRC)/env_panic.c
	$(CC1) $(SRC)/env_panic.c

$(LIBRARY)(env_prefix.o):	$(SRC)/env_prefix.c
	$(CC1) $(SRC)/env_prefix.c

$(LIBRARY)(fkey_ctl.o):	$(SRC)/fkey_ctl.c
	$(CC1) $(SRC)/fkey_ctl.c

$(LIBRARY)(panic.o):	$(SRC)/panic.c
	$(CC1) $(SRC)/panic.c

$(LIBRARY)(report.o):	$(SRC)/report.c
	$(CC1) $(SRC)/report.c

$(LIBRARY)(taskcall.o):	$(SRC)/taskcall.c
	$(CC1) $(SRC)/taskcall.c
