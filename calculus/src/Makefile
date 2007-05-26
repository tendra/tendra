# $Id$


SRC=.
SRCC=obj_c
SRCTOK=obj_tok
SRCX=shared

CFAGS= -I${SRCC} -I${SRCTOK} -I${SRCX}
LIBS=

REMOVE=rm -f
MOVE=mv

#.PATH:	${SRCC} ${SRCTOK} ${SRCX}

SIDOPTS=-l ansi-c -s no-lines

SID_OUT=syntax.c syntax.h
C_OUT=${SRCC}/calculus.h ${SRCC}/type_ops.h
TOK_OUT=${SRCTOK}/calculus.h ${SRCTOK}/type_ops.h
DISK_OUT=read_def.h write_def.h print_def.h
LEXI_OUT=lexer.h keyword.h

all: calculus

syntax.c : syntax.sid syntax.act
	@${REMOVE} ${SID_OUT}
	${SID} ${SIDOPTS} syntax.sid syntax.act ${SID_OUT}

${SRCC}/calculus.h : calculus.alg
	@${REMOVE} ${SRCC}/*.h
	${CALCULUS} -a -x calculus.alg ${SRCC}

${SRCTOK}/calculus.h : calculus.alg
	@${REMOVE} ${SRCTOK}/*.h
	${CALCULUS} -a -x -t calculus.alg ${SRCTOK}

read_def.h : calculus.alg disk.alg
	@${REMOVE} read_def.h write_def.h
	${CALCULUS} -a -x -d calculus.alg disk.alg ${SRC}

print_def.h : calculus.alg
	@${REMOVE} print_def.h
	${CALCULUS} -a -x -p calculus.alg ${SRC}

lexer.h : lexer.lxi
	@${REMOVE} lexer.h
	${LEXI} lexer.lxi lexer.h

keyword.h : lexer.lxi
	@${REMOVE} keyword.h
	${LEXI} -k lexer.lxi keyword.h

#auto_clobber :
#	${REMOVE} ${SID_OUT}
#	${REMOVE} ${SRCC}/*.h
#	${REMOVE} ${SRCTOK}/*.h
#	${REMOVE} ${DISK_OUT}
#	${REMOVE} ${LEXI_OUT}

TARGETS=output.o template.o code.o read.o pretty.o disk.o check.o \
	token.o main.o syntax.o common.o lex.o write.o print.o \
	shared/xalloc.a shared/error.a \
	obj_c/calculus.o

clean:
	rm -f $(TARGETS) calculus

calculus: $(TARGETS)
	$(CC) -o $@ $(CFLAGS) $(LDFLAGS) $(TARGETS)

#syntax.c: syntax.sid syntax.act
#	sid ${SIDOPTS} syntax.sid syntax.act tmp.syntax.c tmp.syntax.h || ( ${REMOVE} tmp-c.$@ tmp-h.$@ ; exit 1 )
#	${MOVE} tmp.syntax.c syntax.c
#	${MOVE} tmp.syntax.h syntax.h

shared/error.a:
	cd shared && make error.a

shared/xalloc.a:
	cd shared && make xalloc.a

obj_c/calculus.o:
	cd obj_c && make calculus.o

