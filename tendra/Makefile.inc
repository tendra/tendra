# $Id$

DIST_DIR:=	${.PARSEDIR}

.MAKEFLAGS:	-m ${DIST_DIR}/mk -r

.if exists(${DIST_DIR}/Makefile.defs)
.include "Makefile.defs"
.endif
.include <tendra.build.mk>
.include <tendra.install.mk>
.include <tendra.compiler.mk>
