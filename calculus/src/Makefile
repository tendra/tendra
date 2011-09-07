# $Id$

.include "Makefile.inc"


PARTS+=	src/shared
PARTS+=	src/obj_c

.include <tendra.partial.mk>


SRCS+=	output.c
SRCS+=	template.c
SRCS+=	code.c
SRCS+=	read.c
SRCS+=	pretty.c
SRCS+=	disk.c
SRCS+=	check.c
SRCS+=	token.c
SRCS+=	main.c
SRCS+=	syntax.c
SRCS+=	common.c
SRCS+=	lex.c
SRCS+=	write.c
SRCS+=	print.c

.include <tendra.obj.mk>


PROG=	calculus

.include <tendra.prog.mk>


SYNTAX+=	syntax.sid

.include <tendra.sid.mk>


#obj_c/calculus.h: calculus.alg
#	@${REMOVE} obj_c/*.h
#	${CALCULUS} -a -x calculus.alg obj_c
#
#obj_tok/calculus.h: calculus.alg
#	@${REMOVE} obj_tok/*.h
#	${CALCULUS} -a -x -t calculus.alg obj_tok
#
#read_def.h: calculus.alg disk.alg
#	@${REMOVE} read_def.h write_def.h
#	${CALCULUS} -a -x -d calculus.alg disk.alg .
#
#print_def.h: calculus.alg
#	@${REMOVE} print_def.h
#	${CALCULUS} -a -x -p calculus.alg .
#
#lexer.h: lexer.lxi
#	@${REMOVE} lexer.h
#	${LEXI} lexer.lxi lexer.h
#
#keyword.h: lexer.lxi
#	@${REMOVE} keyword.h
#	${LEXI} -k lexer.lxi keyword.h
#
#auto_clobber:
#	${REMOVE} obj_c/*.h
#	${REMOVE} obj_tok/*.h
#	${REMOVE} ${DISK_OUT}
#	${REMOVE} ${LEXI_OUT}
#
#obj_c/calculus.o:
#	cd obj_c && ${MAKE} calculus.o

