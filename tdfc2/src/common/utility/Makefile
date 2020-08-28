# $Id$

.include "Makefile.inc"


CCOPTS+=	-I ../../common/construct
CCOPTS+=	-I ../../common/obj_c
CCOPTS+=	-I ../../common/output
CCOPTS+=	-I ../../common/parse
CCOPTS+=	-I ../../common

TCCOPTS.system.c+=	-Yposix

SRCS+=	buffer.c
SRCS+=	catalog.c
SRCS+=	debug.c
SRCS+=	error.c
SRCS+=	option.c
SRCS+=	print.c
SRCS+=	system.c
SRCS+=	xalloc.c

.include <tendra.obj.mk>

.include <tendra.partial.mk>


ERRORS+= 	catalog.err

# TODO: these are silly filenames
ERROR_DECL= 	errors1.h
ERROR_DEFN= 	errors3.h
ERR_USAGE=	opts.h

.include <tendra.errors.mk>

