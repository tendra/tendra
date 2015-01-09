# $Id$

.include "Makefile.inc"

# gen_tokens is just a little helper utility, and is not installed anywhere;
# It's intended to be used by developers who are adding new machines. It's
# only built if -DGENTOKENS is specified to make.
.if defined(GENTOKENS)

SRCS+=	main.c

. include <tendra.obj.mk>


PROG=	gen_tokens

. include <tendra.prog.mk>

.endif

