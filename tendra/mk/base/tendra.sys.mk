# $TenDRA$

.SUFFIXES:	.o .c .c-tdf .h-tdf

CC		?=	cc
CFLAGS		?=	-O -pipe
CXX		?=	c++
CXXFLAGS	?=	${CXXINCLUDES} ${CFLAGS}
CPP		?=	cpp
ECHO		?=	echo
ECHODIR		?=	echo


.c.o:
	${CC} ${CFLAGS} -c ${.IMPSRC}

.c-tdf.c .h-tdf.h:
	${MAKE_TDF} ${.CURDIR}/../../lib/tdf/def_4_1.db ${.IMPSRC} >\
	${OBJ_DIR}/${.TARGET}
