# $Id$

.include "Makefile.inc"


PARTS+=	src/shared
PARTS+=	src/out
PARTS+=	src/adt

.include <tendra.partial.mk>


CCOPTS+=	-I .

SRCS+=	ast.c
SRCS+=	syntax.c
SRCS+=	lexer.c
SRCS+=	main.c
SRCS+=	lctlexer.c
SRCS+=	lctsyntax.c
SRCS+=	code.c

.include <tendra.obj.mk>


PROG=	lexi

.include <tendra.prog.mk>


SIDOPTS+=	-s unreachable-macro

SYNTAX+=	syntax.sid
SYNTAX+=	lctsyntax.sid

.include <tendra.sid.mk>


#LEXIFLAGS+=
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
#	${LEXI} ${LEXIFLAGS} -lc lexer.lxi lexer.lct lexer.c \
#		|| ( ${MOVE} sav.lexer.c lexer.c; exit 1 )
#	-${MOVE} lexer.h sav.lexer.h
#	${LEXI} ${LEXIFLAGS} -lh lexer.lxi lexer.lct lexer.h \
#		|| ( ${MOVE} sav.lexer.h lexer.h; exit 1 )
#
#lctlexer.c lctlexer.h: lctlexer.lxi lctlexer.lct ../doc/copyright/COPYING.dera-cc
#	-${MOVE} lctlexer.c sav.lctlexer.c
#	${LEXI} ${LEXIFLAGS} -lc -t lct_lex_ -p lexi_lct_ lctlexer.lxi lctlexer.lct lctlexer.c \
#		|| ( ${MOVE} sav.lctlexer.c lctlexer.c; exit 1 )
#	-${MOVE} lctlexer.h sav.lctlexer.h
#	${LEXI} ${LEXIFLAGS} -lh -t lct_lex_ -p lexi_lct_ lctlexer.lxi lctlexer.lct lctlexer.h \
#		|| ( ${MOVE} sav.lctlexer.c lctlexer.h; exit 1 )

