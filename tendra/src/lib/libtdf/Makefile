# $Id$

# Standard variables

CC?=		tcc
MACHOPTS=
TCCOPTS=	-Ypl_tdf -jtarget_tok
CCOPTS=${MACHOPTS} ${TCCOPTS}
MAIN_CC=${CC} ${CCOPTS} -c
AR=ar
RANLIB=ranlib
LIBS=

# Dependencies and construction rules

NAME=libtdf.a

OFILES=INT64.o version.o

${NAME} : ${OFILES}
	${AR} cr ${NAME} ${OFILES} ${LIBS}
	${RANLIB} ${NAME}

INT64.o : ${SRC}/INT64a.c ${SRC}/INT64b.pl ${SRC}/abstract.pl\
 ${SRC}/abstract.h ${SRC}/abstract.ph
	${MAIN_CC} -o INT64.o -M -WP,-I${SRC} ${SRC}/INT64a.c ${SRC}/INT64b.pl ${SRC}/abstract.pl

version.o : ${SRC}/version.c
	${MAIN_CC} ${SRC}/version.c
