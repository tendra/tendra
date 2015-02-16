# $Id$

.include "Makefile.inc"


CCOPTS+=	-I ../../common/construct
CCOPTS+=	-I ../../common/obj_c
CCOPTS+=	-I ../../common/output
CCOPTS+=	-I ../../common/parse
CCOPTS+=	-I ../../common/utility
CCOPTS+=	-I ../../common

SRCS!=	ls -1 syntax*.c

.include <tendra.obj.mk>

.include <tendra.partial.mk>


SIDOPTS+=	-s unreachable-macro
SIDOPTS+=	-s split=5000

SYNTAX+=	syntax.sid

.include <tendra.sid.mk>

