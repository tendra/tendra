# $Id$

.include "Makefile.inc"


SUBDIR+=	papers

# The developer documentation is relevant for the website, but not appropriate
# for installation on a users' system. It may be enabled conditionally, by
# specifying -DDEVELOPER to make.
.if defined(DEVELOPER)
SUBDIR+=	developer
.endif

.include <tendra.subdir.mk>

