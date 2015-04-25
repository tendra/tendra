# $Id$

.include "Makefile.inc"


# XXX: The env order is wrong because ENVFILEs are handled after ENVCOMMON,
# but the toolchain environments depend on LIB_CRT* from the "default" env
# here. So we also add this directory to ENVCOMMON in env/, which ensures
# the default environment is processed before those variables are referenced.
#
# This could be more nicely solved by having tcc postpone variable expansion
# until after parse, perhaps.

ENVFILE+=	default

.include <tendra.env.mk>

