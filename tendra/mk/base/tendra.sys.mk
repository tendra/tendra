# $TenDRA$

.SUFFIXES:	.o .c .h .j .pl .c-tdf .h-tdf .cc .t .p .disp

CFLAGS?=	-O -pipe

.c.j:
	${TCC} ${TCC_OPTS} ${TCCFLAGS} -o ${.TARGET} ${.IMPSRC}

.c.o:
	${BIN_CC} ${CFLAGS} -c ${.IMPSRC}

.c-tdf.c .h-tdf.h:
	${MAKE_TDF} ${SRC_DIR}/src/lib/tdf/def_4_1.db ${.IMPSRC} >\
	${OBJ_DIR}/${.TARGET}

.cc.o:
	${TCC} ${TCC_OPTS} ${TCC_FLAGS} -c ${.IMPSRC}

.j.disp:
	${DISP} ${DISP_FLAGS} ${.IMPSRC} ${.TARGET} || (true)

.p.j:
	${TNC} ${.IMPSRC} ${.TARGET}

.pl.j:
	${PL} ${.IMPSRC} ${.TARGET} 

.pl.o:
	${TCC} ${TCC_OPTS} -Ypl_tdf -c ${.IMPSRC}
