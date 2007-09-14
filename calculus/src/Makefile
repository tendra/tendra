# $Id$

SRC=.
SRCC=obj_c
SRCTOK=obj_tok

CPPFLAGS+=	-Ishared/error -Ishared/xalloc
LDFLAGS+=	-Lshared/error -Lshared/xalloc

REMOVE=rm -f
MOVE=mv
CALCULUS=calculus
LEXI=lexi
SID=sid

SIDOPTS=-l ansi-c -s no-lines
SID_OUT=syntax.c syntax.h

OBJS=	output.o template.o code.o read.o pretty.o disk.o check.o \
	token.o main.o syntax.o common.o lex.o write.o print.o \
	obj_c/calculus.o

all: calculus

calculus: depend ${OBJS}
	${CC} -o $@ ${LDFLAGS} ${OBJS} -lerror -lxalloc

syntax.c: syntax.sid syntax.act
	@${REMOVE} ${SID_OUT}
	${SID} ${SIDOPTS} syntax.sid syntax.act ${SID_OUT}

${SRCC}/calculus.h: calculus.alg
	@${REMOVE} ${SRCC}/*.h
	${CALCULUS} -a -x calculus.alg ${SRCC}

${SRCTOK}/calculus.h: calculus.alg
	@${REMOVE} ${SRCTOK}/*.h
	${CALCULUS} -a -x -t calculus.alg ${SRCTOK}

read_def.h: calculus.alg disk.alg
	@${REMOVE} read_def.h write_def.h
	${CALCULUS} -a -x -d calculus.alg disk.alg ${SRC}

print_def.h: calculus.alg
	@${REMOVE} print_def.h
	${CALCULUS} -a -x -p calculus.alg ${SRC}

lexer.h: lexer.lxi
	@${REMOVE} lexer.h
	${LEXI} lexer.lxi lexer.h

keyword.h: lexer.lxi
	@${REMOVE} keyword.h
	${LEXI} -k lexer.lxi keyword.h

#auto_clobber:
#	${REMOVE} ${SID_OUT}
#	${REMOVE} ${SRCC}/*.h
#	${REMOVE} ${SRCTOK}/*.h
#	${REMOVE} ${DISK_OUT}
#	${REMOVE} ${LEXI_OUT}

depend:
	cd shared && ${MAKE} -f makefile.standalone all

obj_c/calculus.o:
	cd obj_c && ${MAKE} calculus.o

clean:
	${REMOVE} ${OBJS} calculus
	cd shared && ${MAKE} -f makefile.standalone clean
