# $Id$

CFLAGS +=	-Ishared/error -Ishared/xalloc
LDFLAGS +=	-Lshared/error -Lshared/xalloc

CALCULUS = calculus
LEXI = lexi
SID = sid
REMOVE = rm -f

# Standard directories and files

SRCC=${.CURDIR}/obj_c
SRCTOK=${.CURDIR}/obj_tok
SRCX=${.CURDIR}/../shared
SRC=${.CURDIR}

# Standard variables

WARNS?=		2

TCCOPTS=	-Yposix2 -Xs
CCOPTS=		${TCCOPTS} -I${BASE_DIR}/${INCLUDE} -I${.CURDIR} -I${SRCC}\
		-I${SRCTOK} -I${SRCX} -I${BASE_DIR}/src/shared/error \
		-I${BASE_DIR}/src/shared/xalloc

LDOPTS=		-L${OBJ_DIR}/src/shared/error -L${OBJ_DIR}/src/shared/xalloc
LIBS=		-lerror -lxalloc
SIDOPTS=-l ansi-c -s no-lines

# Dependencies and construction rules

OBJS = lex.o main.o process.o syntax.o

all: make_err

make_err: depend ${OBJS} obj_c/errors.o
	${CC} -o make_err ${LDFLAGS} ${OBJS} obj_c/errors.o -lerror -lxalloc


#C_OUT=${SRC2}/errors.h
#TOK_OUT=${SRC2A}/errors.h
#LEXI_OUT=${SRC}/lexer.h ${SRC}/keyword.h
#
#auto : ${SID_OUT} ${C_OUT} ${TOK_OUT} ${LEXI_OUT}

syntax.c : syntax.sid syntax.act
	@${REMOVE} syntax.c syntax.h
	${SID} ${SIDOPTS} syntax.sid syntax.act syntax.c syntax.h

${SRCC}/errors.h : ${SRC}/errors.alg
	@${REMOVE} ${SRCC}/*.h
	${CALCULUS} -a -x ${SRC}/errors.alg ${SRCC}

${SRCTOK}/errors.h : ${SRC}/errors.alg
	@${REMOVE} ${SRCTOK}/*.h
	${CALCULUS} -a -x -t ${SRC}/errors.alg ${SRCTOK}

#${SRC}/lexer.h : ${SRC}/lexer.lxi
#	@${REMOVE} ${SRC}/lexer.h
#	${LEXI} ${SRC}/lexer.lxi ${SRC}/lexer.h
#
#${SRC}/keyword.h : ${SRC}/lexer.lxi
#	@${REMOVE} ${SRC}/keyword.h
#	${LEXI} -k ${SRC}/lexer.lxi ${SRC}/keyword.h
#
#auto_clobber :
#	${REMOVE} ${SID_OUT} ${LEXI_OUT}
#	${REMOVE} ${SRC2}/*.h
#	${REMOVE} ${SRC2A}/*.h

obj_c/errors.o:
	cd obj_c && ${MAKE} errors.o

depend:
	cd shared && ${MAKE} -f makefile.standalone all

clean:
	${REMOVE} ${OBJS} make_err
	cd obj_c && ${MAKE} clean
	cd shared && ${MAKE} -f makefile.standalone clean

