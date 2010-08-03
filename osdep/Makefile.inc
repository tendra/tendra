# $Id$

.if !defined(BASE_DIR)
. if !defined(_BASEDIR_RELATIVE)
BASE_DIR!=	cd ${.CURDIR} && pwd
. else
BASE_DIR!=	cd ${_BASEDIR_RELATIVE} && pwd
. endif
.endif

.MAKEFLAGS:	-m ${BASE_DIR}/mk -m ${BASE_DIR}/mk-local -r

