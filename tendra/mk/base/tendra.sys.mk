# $TenDRA$

.SUFFIXES:	.o .c .h .j .pl .c-tdf .h-tdf .cc .t .p .disp

#CC		?=	cc
CFLAGS		?=	-O -pipe
CXX		?=	c++
CXXFLAGS	?=	${CXXINCLUDES} ${CFLAGS}
CPP		?=	cpp
ECHO		?=	echo
ECHODIR		?=	echo


.c.o:
	${BIN_CC} ${CFLAGS} -c ${.IMPSRC}

.c-tdf.c .h-tdf.h:
	${MAKE_TDF} ${SRC_DIR}/src/lib/tdf/def_4_1.db ${.IMPSRC} >\
	${OBJ_DIR}/${.TARGET}

.pl.j:
	${PL} ${.IMPSRC} ${.TARGET} 

.j.disp:
	${DISP} ${DISP_FLAGS} ${.IMPSRC} ${.TARGET} || (true)

.c.j:
	${TCC} ${TCC_OPTS} ${TCCFLAGS} -o ${.TARGET} ${.IMPSRC}

.cc.o:
	${TCC} ${TCC_OPTS} ${TCC_FLAGS} -c ${.IMPSRC}

.p.j:
	${TNC} ${.IMPSRC} ${.TARGET}
