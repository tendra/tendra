# $Id$

.include "Makefile.inc"


PARTS+=	src/shared
PARTS+=	src/exds
PARTS+=	src/adt
PARTS+=	src/lang-bnf
PARTS+=	src/lang-c
PARTS+=	src/lang-test
PARTS+=	src/rules

.include <tendra.partial.mk>


SRCS+=	arg-parse.c
SRCS+=	grammar.c
SRCS+=	lexer.c
SRCS+=	main.c
SRCS+=	output.c
SRCS+=	parser.c
SRCS+=	lexi_lexer.c
SRCS+=	fmt.c

.include <tendra.obj.mk>


PROG=	sid

.include <tendra.prog.mk>


SIDOPTS+=	-s unreachable-macro
SIDOPTS+=	-s numeric
SIDOPTS+=	-s no-terminals
SIDOPTS+=	-s no-numeric-terminals

SYNTAX+=	parser.sid

.include <tendra.sid.mk>


#LEXIOPTS=-lC90 -a
#
#lexi_lexer.h lexi_lexer.c: lexi_lexer.lxi lexi_lexer.lct
#	-${MOVE} lexi_lexer.c sav.lexi_lexer.c 
#	-${MOVE} lexi_lexer.h sav.lexi_lexer.h
#	${LEXI} ${LEXIOPTS} -t LEXER_TOK_ lexi_lexer.lxi lexi_lexer.lct lexi_lexer.c lexi_lexer.h \
#		|| ( ${MOVE} sav.lexi_lexer.c lexi_lexer.c ; ${MOVE} sav.lexi_lexer.h lexi_lexer.h ; exit 1 )

