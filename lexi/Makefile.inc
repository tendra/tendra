# $Id$

.if !defined(BASE_DIR)
. if "${_BASEDIR_RELATIVE}" == ""
BASE_DIR!=	cd ${.CURDIR} && pwd
. else
BASE_DIR!=	cd ${_BASEDIR_RELATIVE} && pwd
. endif
.endif

.if exists(${BASE_DIR}/Makefile.defs)
. include "${BASE_DIR}/Makefile.defs"
.endif

.MAKEFLAGS:	-m ${BASE_DIR}/mk -m ${BASE_DIR}/mk-local -r

