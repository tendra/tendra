# $Id$

.include "Makefile.inc"

# The .tpl files here are used directly from lib/machines/*/*/tokens; they are
# not built from this Makefile (that is, its 'all' target is not used).


# gen_tokens is just a little helper utility, and is not installed anywhere;
# It's intended to be used by developers who are adding new machines. It's
# only built if -DGENTOKENS is specified to make.
.if defined(GENTOKENS)

SRCS+=	gen_tokens.c

. include <tendra.obj.mk>


PROG=	gen_tokens

. include <tendra.prog.mk>

.endif

