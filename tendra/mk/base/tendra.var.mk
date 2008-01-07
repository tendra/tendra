# $TenDRA$

# Calculate our object directory and obj prefix.
OBJ_PREFIX?=	${.CURDIR:C/(.*)\/src(.*)/\1\/obj/}
OBJ_DIR=	${.CURDIR:C/(.*)\/src(.*)/${OBJ_PREFIX}\/\2/}

.if !defined(SRC_DIR)
SRC_DIR=        ${.CURDIR:C/(.*)\/src.*/\1/}
.endif
