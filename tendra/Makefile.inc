# $Id$

DIST_DIR = ${.CURDIR:C/\/src.*//}

.MAKEFLAGS: -m ${DIST_DIR}/mk -r

.include "Makefile.defs"
.include <tendra.build.mk>
.include <tendra.compiler.mk>
