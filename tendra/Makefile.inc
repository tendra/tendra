# $Id$

DIST_DIR:=	${.PARSEDIR}

.MAKEFLAGS:	-m ${DIST_DIR}/mk -r

.sinclude "Makefile.defs"
.if defined(BOOTSTRAP)
.include <tendra.bootstrap.mk>
.else
.include <tendra.build.mk>
.endif
.include <tendra.install.mk>
.include <tendra.compiler.mk>
