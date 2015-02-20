# $Id$

.include "Makefile.inc"


CCOPTS+=	-I construct
CCOPTS+=	-I parse
CCOPTS+=	-I obj_c
CCOPTS+=	-I output
CCOPTS+=	-I .

TCCOPTS+= -Yposix

SRCS+=	main.c

.include <tendra.obj.mk>

.include <tendra.partial.mk>


ALGEBRA_C+=  	c_class.alg
ALGEBRA_TOK+=	c_class.alg

TEMPLATES+=	bits.h
TEMPLATES+=	err_ext.h
TEMPLATES+=	loc_ext.h

.include <tendra.calculus.mk>

