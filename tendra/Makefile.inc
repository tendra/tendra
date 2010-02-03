.if !defined(BASE_DIR)
BASE_DIR!=	cd ${.CURDIR}/${_BASEDIR_RELATIVE} && pwd
.endif

.if exists(${BASE_DIR}/Makefile.defs)
. include "${BASE_DIR}/Makefile.defs"
.endif

.MAKEFLAGS:	-m ${BASE_DIR}/mk -r

.include <tendra.build.mk>
.include <tendra.install.mk>
.include <tendra.compiler.mk>
