# $Id$

CFLAGS +=	-Ishared/error -Ishared/xalloc
LDFLAGS +=	-Lshared/error -Lshared/xalloc

CALCULUS = calculus
REMOVE = rm -f
LEXI = lexi
SID = sid

# Standard directories and files

SRCC=${.CURDIR}/obj_c
SRCTOK=${.CURDIR}/obj_tok
SRCX=${.CURDIR}/../shared
SRC=${.CURDIR}

# Standard variables

WARNS?=		2

TCCOPTS=	-Yansi -Xs
CCOPTS=		${TCCOPTS} -I${BASE_DIR}/${INCLUDE} -I${.CURDIR} -I${SRCC}\
		-I${SRCTOK} -I${SRCX} -I${BASE_DIR}/src/shared/error \
		-I${BASE_DIR}/src/shared/xalloc

LDOPTS=		-L${OBJ_DIR}/src/shared/error -L${OBJ_DIR}/src/shared/xalloc
LIBS=		-lerror -lxalloc

# Dependencies and construction rules

OBJS = input.o lex.o main.o output.o syntax.o

#SIDOPTS=-l ansi-c -s no-lines
#C_OUT=${SRC2}/tdf.h
#TOK_OUT=${SRC2A}/tdf.h
#LEXI_OUT=${SRC}/lexer.h ${SRC}/keyword.h
#
#auto : ${SID_OUT} ${C_OUT} ${TOK_OUT} ${LEXI_OUT}

# XXX what uses obj_tok/?

all: make_tdf

make_tdf: depend ${OBJS} obj_c/tdf.o
	${CC} -o make_tdf ${LDFLAGS} ${OBJS} obj_c/tdf.o -lerror -lxalloc

syntax.c : syntax.sid syntax.act
	@${REMOVE} syntax.c syntax.h
	${SID} ${SIDOPTS} syntax.sid syntax.act syntax.c syntax.h

${SRCC}/tdf.h : ${SRC}/tdf.alg
	@${REMOVE} ${SRCC}/*.h
	${CALCULUS} -a -x ${SRC}/tdf.alg ${SRCC}

${SRCTOK}/tdf.h : ${SRC}/tdf.alg
	@${REMOVE} ${SRCTOK}/*.h
	${CALCULUS} -a -x -t ${SRC}/tdf.alg ${SRCTOK}

#${SRC}/lexer.h : ${SRC}/lexer.lxi
#	@${REMOVE} ${SRC}/lexer.h
#	${LEXI} ${SRC}/lexer.lxi ${SRC}/lexer.h
#
#${SRC}/keyword.h : ${SRC}/lexer.lxi
#	@${REMOVE} ${SRC}/keyword.h
#	${LEXI} -k ${SRC}/lexer.lxi ${SRC}/keyword.h

obj_c/tdf.o:
	cd obj_c && ${MAKE} tdf.o

depend:
	cd shared && ${MAKE} -f makefile.standalone all

clean:
	${REMOVE} ${OBJS} make_tdf
	cd obj_c && ${MAKE} clean
	cd shared && ${MAKE} -f makefile.standalone clean

