# Makefile for lib/syslib.

SRC=/usr/src/lib/syslib
LIBRARY=$(NAME)
CC1=tcc -Ysystem -c -I$(SRC)

all: $(LIBRARY)

OBJECTS	= \
	$(LIBRARY)(sys_times.o) \
	$(LIBRARY)(sys_abort.o) \
	$(LIBRARY)(sys_exec.o) \
	$(LIBRARY)(sys_fork.o) \
	$(LIBRARY)(sys_int86.o) \
	$(LIBRARY)(sys_kill.o) \
	$(LIBRARY)(sys_newmap.o) \
	$(LIBRARY)(sys_sigsend.o) \
	$(LIBRARY)(sys_sigreturn.o) \
	$(LIBRARY)(sys_endsig.o) \
	$(LIBRARY)(sys_getsig.o) \
	$(LIBRARY)(sys_svrctl.o) \
	$(LIBRARY)(sys_trace.o) \
	$(LIBRARY)(sys_exit.o) \
	$(LIBRARY)(sys_sdevio.o) \
	$(LIBRARY)(sys_getinfo.o) \
	$(LIBRARY)(sys_irqctl.o) \
	$(LIBRARY)(sys_segctl.o) \
	$(LIBRARY)(sys_nice.o) \
	$(LIBRARY)(sys_umap.o) \
	$(LIBRARY)(sys_physcopy.o) \
	$(LIBRARY)(sys_vircopy.o) \
	$(LIBRARY)(sys_in.o) \
	$(LIBRARY)(sys_out.o) \
	$(LIBRARY)(sys_vinb.o) \
	$(LIBRARY)(sys_vinw.o) \
	$(LIBRARY)(sys_vinl.o) \
	$(LIBRARY)(sys_voutb.o) \
	$(LIBRARY)(sys_voutw.o) \
	$(LIBRARY)(sys_voutl.o) \
	$(LIBRARY)(sys_setalarm.o) \
	$(LIBRARY)(sys_memset.o) \
	$(LIBRARY)(taskcall.o) \

$(LIBRARY):	$(OBJECTS)
	aal cr $@ *.o
	rm *.o

$(LIBRARY)(sys_times.o):	$(SRC)/sys_times.c
	$(CC1) $(SRC)/sys_times.c

$(LIBRARY)(sys_abort.o):	$(SRC)/sys_abort.c
	$(CC1) $(SRC)/sys_abort.c

$(LIBRARY)(sys_exec.o):	$(SRC)/sys_exec.c
	$(CC1) $(SRC)/sys_exec.c

$(LIBRARY)(sys_fork.o):	$(SRC)/sys_fork.c
	$(CC1) $(SRC)/sys_fork.c

$(LIBRARY)(sys_int86.o):	$(SRC)/sys_int86.c
	$(CC1) $(SRC)/sys_int86.c

$(LIBRARY)(sys_kill.o):	$(SRC)/sys_kill.c
	$(CC1) $(SRC)/sys_kill.c

$(LIBRARY)(sys_newmap.o):	$(SRC)/sys_newmap.c
	$(CC1) $(SRC)/sys_newmap.c

$(LIBRARY)(sys_sigsend.o):	$(SRC)/sys_sigsend.c
	$(CC1) $(SRC)/sys_sigsend.c

$(LIBRARY)(sys_sigreturn.o):	$(SRC)/sys_sigreturn.c
	$(CC1) $(SRC)/sys_sigreturn.c

$(LIBRARY)(sys_endsig.o):	$(SRC)/sys_endsig.c
	$(CC1) $(SRC)/sys_endsig.c

$(LIBRARY)(sys_getsig.o):	$(SRC)/sys_getsig.c
	$(CC1) $(SRC)/sys_getsig.c

$(LIBRARY)(sys_svrctl.o):	$(SRC)/sys_svrctl.c
	$(CC1) $(SRC)/sys_svrctl.c

$(LIBRARY)(sys_trace.o):	$(SRC)/sys_trace.c
	$(CC1) $(SRC)/sys_trace.c

$(LIBRARY)(sys_exit.o):	$(SRC)/sys_exit.c
	$(CC1) $(SRC)/sys_exit.c

$(LIBRARY)(sys_sdevio.o):	$(SRC)/sys_sdevio.c
	$(CC1) $(SRC)/sys_sdevio.c

$(LIBRARY)(sys_getinfo.o):	$(SRC)/sys_getinfo.c
	$(CC1) $(SRC)/sys_getinfo.c

$(LIBRARY)(sys_irqctl.o):	$(SRC)/sys_irqctl.c
	$(CC1) $(SRC)/sys_irqctl.c

$(LIBRARY)(sys_segctl.o):	$(SRC)/sys_segctl.c
	$(CC1) $(SRC)/sys_segctl.c

$(LIBRARY)(sys_nice.o):	$(SRC)/sys_nice.c
	$(CC1) $(SRC)/sys_nice.c

$(LIBRARY)(sys_umap.o):	$(SRC)/sys_umap.c
	$(CC1) $(SRC)/sys_umap.c

$(LIBRARY)(sys_physcopy.o):	$(SRC)/sys_physcopy.c
	$(CC1) $(SRC)/sys_physcopy.c

$(LIBRARY)(sys_vircopy.o):	$(SRC)/sys_vircopy.c
	$(CC1) $(SRC)/sys_vircopy.c

$(LIBRARY)(sys_in.o):	$(SRC)/sys_in.c
	$(CC1) $(SRC)/sys_in.c

$(LIBRARY)(sys_out.o):	$(SRC)/sys_out.c
	$(CC1) $(SRC)/sys_out.c

$(LIBRARY)(sys_vinb.o):	$(SRC)/sys_vinb.c
	$(CC1) $(SRC)/sys_vinb.c

$(LIBRARY)(sys_vinw.o):	$(SRC)/sys_vinw.c
	$(CC1) $(SRC)/sys_vinw.c

$(LIBRARY)(sys_vinl.o):	$(SRC)/sys_vinl.c
	$(CC1) $(SRC)/sys_vinl.c

$(LIBRARY)(sys_voutb.o):	$(SRC)/sys_voutb.c
	$(CC1) $(SRC)/sys_voutb.c

$(LIBRARY)(sys_voutw.o):	$(SRC)/sys_voutw.c
	$(CC1) $(SRC)/sys_voutw.c

$(LIBRARY)(sys_voutl.o):	$(SRC)/sys_voutl.c
	$(CC1) $(SRC)/sys_voutl.c

$(LIBRARY)(sys_setalarm.o):	$(SRC)/sys_setalarm.c
	$(CC1) $(SRC)/sys_setalarm.c

$(LIBRARY)(sys_memset.o):	$(SRC)/sys_memset.c
	$(CC1) $(SRC)/sys_memset.c

$(LIBRARY)(taskcall.o):	$(SRC)/taskcall.c
	$(CC1) $(SRC)/taskcall.c
