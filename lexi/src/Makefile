# $Id$

.include "Makefile.inc"


PART_CFLAGS+=	-I${.CURDIR}/shared

PARTS+=	src/shared/error
PARTS+=	src/shared/xalloc
PARTS+=	src/exds
PARTS+=	src/output-c
PARTS+=	src/output-dot
PARTS+=	src/adt

.include <tendra.partial.mk>


CCOPTS+=	-Ishared
CCOPTS+=	-I.

CFLAGS+=	-I${BASE_DIR}/include

SRCS+=	syntax.c
SRCS+=	lexer.c
SRCS+=	main.c
SRCS+=	options.c
SRCS+=	output.c
SRCS+=	lctlexer.c
SRCS+=	lctsyntax.c
SRCS+=	adt.c
SRCS+=	ccode.c
SRCS+=	localnames.c

.include <tendra.obj.mk>


PROG=	lexi

.include <tendra.prog.mk>


#LEXIFLAGS+=-lC99 -a
#SIDFLAGS+=-s no-line
#
#lexer.o: lexer.h
#syntax.o: lexer.h
#
#lexer.o main.o syntax.o : syntax.h
#main.o : output-c/c-output.h output-dot/dot-output.h lctlexer.h lexer.h lctsyntax.h
#main.o options.o : options.h
#lctlexer.o : lctsyntax.h lctlexer.h
#
#lexer.c lexer.h: lexer.lxi lexer.lct COPYING
#	-${MOVE} lexer.c sav.lexer.c 
#	-${MOVE} lexer.h sav.lexer.h
#	${LEXI} ${LEXIFLAGS} lexer.lxi lexer.lct lexer.c lexer.h \
#		|| ( ${MOVE} sav.lexer.c lexer.c ; ${MOVE} sav.lexer.h lexer.h ; exit 1 )
#
#lctlexer.c lctlexer.h: lctlexer.lxi lctlexer.lct COPYING
#	-${MOVE} lctlexer.c sav.lctlexer.c
#	-${MOVE} lctlexer.h sav.lctlexer.h
#	${LEXI} ${LEXIFLAGS} -t lct_lex_ -p lexi_lct_ lctlexer.lxi lctlexer.lct lctlexer.c lctlexer.h \
#		|| ( ${MOVE} sav.lctlexer.c lctlexer.c ; ${MOVE} sav.lctlexer.h lctlexer.h ; exit 1 )
#
#
#
#syntax.h: syntax.c
#
#syntax.c: syntax.sid syntax.act
#	@${REMOVE} syntax.h syntax.c
#	${SID} ${SIDFLAGS} syntax.sid syntax.act tmp.syntax.c tmp.syntax.h \
#		|| ( ${REMOVE} tmp.syntax.{c,h} ; exit 1 )
#	${MOVE} tmp.syntax.c syntax.c
#	${MOVE} tmp.syntax.h syntax.h
#
#
#lctsyntax.c lctsyntax.h : lctsyntax.sid lctsyntax.act
#	sid -l ansi-c lctsyntax.sid lctsyntax.act lctsyntax.c lctsyntax.h

