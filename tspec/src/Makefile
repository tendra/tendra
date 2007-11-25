# $Id$

DEST=${OBJ_DIR}/src/lib
#SRC=${BASE}/src/tools/tspec
API_DIR=${BASE_DIR}/src/lib/apis

TCCOPTS=	-Yposix1 -Xs
CCOPTS=		-I${BASE_DIR}/${INCLUDE} -I${.CURDIR}

TARGETS = hash.o index.o lex.o main.o makefile.o name.o object.o print.o \
		syntax.o type.o utility.o variable.o

REMOVE = rm -f
#LEXI=lexi
#SID=sid
#SIDOPTS=-l ossg-c -s no-lines
#
#SID_OUT=${SRC}/syntax.c ${SRC}/syntax.h
#LEXI_OUT=${SRC}/lexer.h ${SRC}/keyword.h


all: tspec

clean:
	$(REMOVE) tspec $(TARGETS)

tspec: $(TARGETS)
	$(CC) -o $@ $(TARGETS)



#auto : ${SID_OUT} ${LEXI_OUT}
#
#${SRC}/syntax.c : ${SRC}/syntax.sid ${SRC}/syntax.act
#	@${REMOVE} ${SID_OUT}
#	${SID} ${SIDOPTS} ${SRC}/syntax.sid ${SRC}/syntax.act ${SID_OUT}
#
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

