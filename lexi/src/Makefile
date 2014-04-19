# $Id$

.include "Makefile.inc"


PARTS+=	src/shared
PARTS+=	src/exds
PARTS+=	src/out
PARTS+=	src/adt

.include <tendra.partial.mk>


CCOPTS+=	-I .

SRCS+=	ast.c
SRCS+=	syntax.c
SRCS+=	lexer.c
SRCS+=	main.c
SRCS+=	options.c
SRCS+=	lctlexer.c
SRCS+=	lctsyntax.c
SRCS+=	ccode.c

.include <tendra.obj.mk>


PROG=	lexi

.include <tendra.prog.mk>


SYNTAX+=	syntax.sid
SYNTAX+=	lctsyntax.sid

.include <tendra.sid.mk>


#LEXIFLAGS+=-lC99 -a
#
#lexer.o: lexer.h
#syntax.o: lexer.h
#
#lexer.o main.o syntax.o : syntax.h
#main.o : output-c/c-output.h output-dot/dot-output.h lctlexer.h lexer.h lctsyntax.h
#main.o options.o : options.h
#lctlexer.o : lctsyntax.h lctlexer.h
#
#lexer.c lexer.h: lexer.lxi lexer.lct ../doc/copyright/COPYING.dera-cc
#	-${MOVE} lexer.c sav.lexer.c 
#	-${MOVE} lexer.h sav.lexer.h
#	${LEXI} ${LEXIFLAGS} lexer.lxi lexer.lct lexer.c lexer.h \
#		|| ( ${MOVE} sav.lexer.c lexer.c ; ${MOVE} sav.lexer.h lexer.h ; exit 1 )
#
#lctlexer.c lctlexer.h: lctlexer.lxi lctlexer.lct ../doc/copyright/COPYING.dera-cc
#	-${MOVE} lctlexer.c sav.lctlexer.c
#	-${MOVE} lctlexer.h sav.lctlexer.h
#	${LEXI} ${LEXIFLAGS} -t lct_lex_ -p lexi_lct_ lctlexer.lxi lctlexer.lct lctlexer.c lctlexer.h \
#		|| ( ${MOVE} sav.lctlexer.c lctlexer.c ; ${MOVE} sav.lctlexer.h lctlexer.h ; exit 1 )

