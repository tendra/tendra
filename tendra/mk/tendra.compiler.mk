# TenDRA make compiler infrastructure
#
# $Id$

.if !defined(_TENDRA_COMPILER_MK_)
_TENDRA_COMPILER_MK_=1

.if defined(BOOTSTRAP)
CC?= cc
CCOPTS+= ${CFLAGS}
LDOPTS+= ${LDFLAGS}

TCC= ${BOBJ_DIR}/src/tools/tcc/tcc \
     -Y${OBJ_DIR}/src/lib/env/build \
     -yTENDRA_BASEDIR=${OBJ_DIR}/src

.else

. if exists(${BOBJ_DIR}/src/tools/tcc/tcc)
TCC= ${BOBJ_DIR}/src/tools/tcc/tcc \
     -Y${BOBJ_DIR}/src/lib/env/build \
     -yTENDRA_BASEDIR=${BOBJ_DIR}/src
. else
TCC?= tcc
. endif

CC= ${TCC}
.endif

CCOPTS+=	-D_${OSVER}

.if exists(${BOBJ_DIR}/src/tools/tspec/tspec)
TSPEC?=	${BOBJ_DIR}/src/tools/tspec/tspec
.else
TSPEC?=	tspec
.endif

.endif	# !defined(_TENDRA_COMPILER_MK_)
