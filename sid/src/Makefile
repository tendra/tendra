# $Id$

.include "Makefile.inc"


PART_CFLAGS+= -I${.CURDIR}/shared

PARTS+=	src/shared/error
PARTS+=	src/exds
PARTS+=	src/adt
PARTS+=	src/lang-bnf
PARTS+=	src/lang-c
PARTS+=	src/lang-test
PARTS+=	src/rules

.include <tendra.partial.mk>


CFLAGS+= -I${BASE_DIR}/include

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


#SIDOPTS=-l ansi-c -s numeric -s no-terminals -s no-numeric-terminals
#LEXIOPTS=-lC90 -a
#
#parser.c: parser.sid parser.act
#	${SID} ${SIDOPTS} parser.sid parser.act tmp.$@ junk.h \
#		|| ( ${REMOVE} tmp.$@ ; exit 1 )
#	${MOVE} tmp.$@ $@
#
#lexi_lexer.h lexi_lexer.c: lexi_lexer.lxi lexi_lexer.lct
#	-${MOVE} lexi_lexer.c sav.lexi_lexer.c 
#	-${MOVE} lexi_lexer.h sav.lexi_lexer.h
#	${LEXI} ${LEXIOPTS} -t LEXER_TOK_ lexi_lexer.lxi lexi_lexer.lct lexi_lexer.c lexi_lexer.h \
#		|| ( ${MOVE} sav.lexi_lexer.c lexi_lexer.c ; ${MOVE} sav.lexi_lexer.h lexi_lexer.h ; exit 1 )

