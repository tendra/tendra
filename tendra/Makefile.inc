# $Id$

BASE_DIR?=	${.CURDIR:C/\/(mk|src).*//}

.MAKEFLAGS:	-m ${BASE_DIR}/mk -r

.if exists(${BASE_DIR}/Makefile.defs)
.include "Makefile.defs"
.endif
.if defined(BOOTSTRAP)
.include <tendra.bootstrap.mk>
.else
.include <tendra.build.mk>
.endif
.if !defined(BOOTSTRAP)
.include <tendra.install.mk>
.endif
.include <tendra.compiler.mk>
