# $Id$

# Standard variables

TCCOPTS=-Y${OBJ_DIR}/${ENVIRONMENT}/bootstrap -yTENDRA_BASEDIR="${OBJ_DIR}/src" -Yc++ -I${SRC}
CCOPTS=${TCCOPTS} ${MACHOPTS}

# Dependencies and construction rules

NAME=libcpp.a
EXTRA=
EXTRA_CLEAN=
EXTRA_CLOBBER=

OFILES=baseinfo.o cmath.o cstring.o cwchar.o exception.o new.o new1.o\
 new2.o new3.o new4.o new5.o new6.o new7.o new8.o pure.o term.o typeinfo.o\
 what.o

${NAME}: ${OFILES}
	${AR} cr ${NAME} ${OFILES} ${LIBS}
	${RANLIB} ${NAME}

all: ${EXTRA} ${NAME}
	@${ECHO} all done

extra: ${EXTRA}
	@${ECHO} done

baseinfo.o: baseinfo.cc
	${TCC} ${TCCOPTS} -c baseinfo.cc

cmath.o: cmath.cc
	${TCC} ${TCCOPTS} -c cmath.cc

cstring.o: cstring.cc
	${TCC} ${TCCOPTS} -c cstring.cc

cwchar.o: cwchar.cc
	${TCC} ${TCCOPTS} -c cwchar.cc

exception.o: exception.cc
	${TCC} ${TCCOPTS} -c exception.cc

new.o: new.cc
	${TCC} ${TCCOPTS} -c new.cc

new1.o: new1.cc
	${TCC} ${TCCOPTS} -c new1.cc

new2.o: new2.cc
	${TCC} ${TCCOPTS} -c new2.cc

new3.o: new3.cc
	${TCC} ${TCCOPTS} -c new3.cc

new4.o: new4.cc
	${TCC} ${TCCOPTS} -c new4.cc

new5.o: new5.cc
	${TCC} ${TCCOPTS} -c new5.cc

new6.o: new6.cc
	${TCC} ${TCCOPTS} -c new6.cc

new7.o: new7.cc
	${TCC} ${TCCOPTS} -c new7.cc

new8.o: new8.cc
	${TCC} ${TCCOPTS} -c new8.cc

pure.o: pure.cc
	${TCC} ${TCCOPTS} -c pure.cc

term.o: term.cc
	${TCC} ${TCCOPTS} -c term.cc

typeinfo.o: typeinfo.cc
	${TCC} ${TCCOPTS} -c typeinfo.cc

what.o: what.cc
	${TCC} ${TCCOPTS} -c what.cc

clobber : clean ${EXTRA_CLOBBER}
	${REMOVE} ${NAME}
