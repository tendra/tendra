# $Id: Makefile.inc 3487 2015-01-07 16:07:18Z kate $

.if !defined(BASE_DIR)
. if !defined(_BASEDIR_RELATIVE)
BASE_DIR!=	cd ${.CURDIR} && pwd
. else
BASE_DIR!=	cd ${_BASEDIR_RELATIVE} && pwd
. endif
.endif

.MAKEFLAGS:	-m ${BASE_DIR}/shared/mk -r

