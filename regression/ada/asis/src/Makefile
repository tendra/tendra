# $TenDRA: Makefile 1621 2004-03-08 06:37:46Z bp $

SRC_DIR =        ${.CURDIR:C/(.*)\/regression.*/\1/}

.include "${.CURDIR}/../test_list.mk"

SUBDIR= ${TESTS}

.include "${SRC_DIR}/mk/base/tendra.subdir.mk"

