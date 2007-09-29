# $Id$

REMOVE = rm -f

CFLAGS += -I../shared/error -I../shared/xalloc

HEADERS = assert_def.h map_ops.h name_ops.h entry_ops.h \
	errors.h msg_ops.h param_ops.h

errors.o: errors.c ${HEADERS}
	${CC} -c ${CFLAGS} errors.c

clean:
	${REMOVE} errors.o

