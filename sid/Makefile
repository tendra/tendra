# $Id$

.include "Makefile.inc"


.if !exists(Makefile.defs)
.BEGIN:
	@${ECHO} "Please run 'makedefs' prior to running (b)make"
	@${ECHO}
	@${EXIT} 1;
.endif


SUBDIR=		src

.include <tendra.subdir.mk>

