# $Id$

DIST_DIR:=	${.PARSEDIR}

.MAKEFLAGS:	-m ${DIST_DIR}/mk -r

.include "Makefile.defs"
.include <tendra.build.mk>
.include <tendra.compiler.mk>
