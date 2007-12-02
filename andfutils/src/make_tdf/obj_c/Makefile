# $Id$

REMOVE = rm -f

CFLAGS += -I../shared/error -I../shared/xalloc

HEADERS = assert_def.h cons_ops.h link_ops.h sort_ops.h \
	cmd_ops.h info_ops.h par_ops.h spec_ops.h tdf.h

tdf.o: tdf.c $(HEADERS)
	${CC} $(CFLAGS) -c tdf.c

clean:
	${REMOVE} tdf.o

