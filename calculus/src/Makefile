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


SIDOPTS+=	-s unreachable-macro

SYNTAX+=	syntax.sid

.include <tendra.sid.mk>


ALGEBRA_C+=  	calculus.alg
ALGEBRA_TOK+=	calculus.alg
ALGEBRA_DISK+=	calculus.alg disk.alg
ALGEBRA_PRINT+=	calculus.alg

.include <tendra.calculus.mk>


#lexer.h: lexer.lxi
#	@${RMFILE} lexer.h
#	${LEXI} lexer.lxi lexer.h
#
#keyword.h: lexer.lxi
#	@${RMFILE} keyword.h
#	${LEXI} -k lexer.lxi keyword.h
#
#auto_clobber:
#	${RMFILE} ${DISK_OUT}
#	${RMFILE} ${LEXI_OUT}

