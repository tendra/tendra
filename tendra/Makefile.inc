# $Id$

DIST_DIR:=	${.PARSEDIR}

.MAKEFLAGS:	-m ${DIST_DIR}/mk -r

.sinclude "Makefile.defs"
.include <tendra.build.mk>
.include <tendra.install.mk>
.include <tendra.compiler.mk>
