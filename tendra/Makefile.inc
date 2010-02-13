# $Id$

.if !defined(BASE_DIR)
. if "${_BASEDIR_RELATIVE}" == ""
BASE_DIR!=	pwd
. else
BASE_DIR!=	cd ${_BASEDIR_RELATIVE} && pwd
. endif
.endif

.if exists(${BASE_DIR}/Makefile.defs)
. include "${BASE_DIR}/Makefile.defs"
.endif

.MAKEFLAGS:	-m ${BASE_DIR}/mk -r

.include <tendra.compiler.mk>

