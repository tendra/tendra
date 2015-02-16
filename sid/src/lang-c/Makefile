# $Id$

.include "Makefile.inc"


SRCS+=	c-main.c
SRCS+=	c-check.c
SRCS+=	c-code.c
SRCS+=	c-lexer.c
SRCS+=	c-out-info.c
SRCS+=	c-out-key.c
SRCS+=	c-out-nl.c
SRCS+=	c-out-types.c
SRCS+=	c-output.c
SRCS+=	c-parser.c
SRCS+=	c-lexi_lexer.c
SRCS+=	persistent.c

.include <tendra.obj.mk>

.include <tendra.partial.mk>


SIDOPTS+=	-s unreachable-macro
SIDOPTS+=	-s numeric
SIDOPTS+=	-s no-terminals
SIDOPTS+=	-s no-numeric-terminals

SYNTAX+=	c-parser.sid

.include <tendra.sid.mk>


#LEXIOPTS=-lC90 -a
#
#c-lexi_lexer.h c-lexi_lexer.c: c-lexi_lexer.lxi c-lexi_lexer.lct
#	-${MOVE} c-lexi_lexer.c sav.c-lexi_lexer.c 
#	-${MOVE} c-lexi_lexer.h sav.c-lexi_lexer.h
#	${LEXI} ${LEXIOPTS} -t C_TOK_ -p c_lexi_ c-lexi_lexer.lxi c-lexi_lexer.lct c-lexi_lexer.c c-lexi_lexer.h \
#		|| ( ${MOVE} sav.c-lexi_lexer.c c-lexi_lexer.c ; ${MOVE} sav.c-lexi_lexer.h c-lexi_lexer.h ; exit 1 )

