# Makefile for lib/syslib.

SRC=/usr/src/lib/syslib
LIBRARY=$(NAME)
CC1=tcc -Ysystem -c -I$(SRC)

all: $(LIBRARY)

OBJECTS	= \
	$(LIBRARY)(sys_abort.o) \
	$(LIBRARY)(sys_copy.o) \
	$(LIBRARY)(sys_endsig.o) \
	$(LIBRARY)(sys_exec.o) \
	$(LIBRARY)(sys_fork.o) \
	$(LIBRARY)(sys_fresh.o) \
	$(LIBRARY)(sys_getmap.o) \
	$(LIBRARY)(sys_getsp.o) \
	$(LIBRARY)(sys_kill.o) \
	$(LIBRARY)(sys_newmap.o) \
	$(LIBRARY)(sys_oldsig.o) \
	$(LIBRARY)(sys_sendsig.o) \
	$(LIBRARY)(sys_sigret.o) \
	$(LIBRARY)(sys_times.o) \
	$(LIBRARY)(sys_trace.o) \
	$(LIBRARY)(sys_xit.o) \
	$(LIBRARY)(taskcall.o) \

$(LIBRARY):	$(OBJECTS)
	aal cr $@ *.o
	rm *.o

$(LIBRARY)(sys_abort.o):	$(SRC)/sys_abort.c
	$(CC1) $(SRC)/sys_abort.c

$(LIBRARY)(sys_copy.o):	$(SRC)/sys_copy.c
	$(CC1) $(SRC)/sys_copy.c

$(LIBRARY)(sys_endsig.o):	$(SRC)/sys_endsig.c
	$(CC1) $(SRC)/sys_endsig.c

$(LIBRARY)(sys_exec.o):	$(SRC)/sys_exec.c
	$(CC1) $(SRC)/sys_exec.c

$(LIBRARY)(sys_fork.o):	$(SRC)/sys_fork.c
	$(CC1) $(SRC)/sys_fork.c

$(LIBRARY)(sys_fresh.o):	$(SRC)/sys_fresh.c
	$(CC1) $(SRC)/sys_fresh.c

$(LIBRARY)(sys_getmap.o):	$(SRC)/sys_getmap.c
	$(CC1) $(SRC)/sys_getmap.c

$(LIBRARY)(sys_getsp.o):	$(SRC)/sys_getsp.c
	$(CC1) $(SRC)/sys_getsp.c

$(LIBRARY)(sys_kill.o):	$(SRC)/sys_kill.c
	$(CC1) $(SRC)/sys_kill.c

$(LIBRARY)(sys_newmap.o):	$(SRC)/sys_newmap.c
	$(CC1) $(SRC)/sys_newmap.c

$(LIBRARY)(sys_oldsig.o):	$(SRC)/sys_oldsig.c
	$(CC1) $(SRC)/sys_oldsig.c

$(LIBRARY)(sys_sendsig.o):	$(SRC)/sys_sendsig.c
	$(CC1) $(SRC)/sys_sendsig.c

$(LIBRARY)(sys_sigret.o):	$(SRC)/sys_sigret.c
	$(CC1) $(SRC)/sys_sigret.c

$(LIBRARY)(sys_times.o):	$(SRC)/sys_times.c
	$(CC1) $(SRC)/sys_times.c

$(LIBRARY)(sys_trace.o):	$(SRC)/sys_trace.c
	$(CC1) $(SRC)/sys_trace.c

$(LIBRARY)(sys_xit.o):	$(SRC)/sys_xit.c
	$(CC1) $(SRC)/sys_xit.c

$(LIBRARY)(taskcall.o):	$(SRC)/taskcall.c
	$(CC1) $(SRC)/taskcall.c
