# $TenDRA$
#
# This include is only for building the libraries.

#.PATH : ${.OBJDIR}.api  /mnt/free/tendra/new/obj/lib/apis/lib

TLD_FLAGS+=	-mc

TCC_OPTS+=      -yTENDRA_BASEDIR=${OBJ_PREFIX}

TCC_OPTS+=	-Fj \
		-Y${DEFAULT_BUILD} \
		-Ybuilding \
		-Y32bit

TCCFLAGS+=	-I${OBJ_PREFIX}/lib/machines/${SRC_MACHINES}/include \
		-I/usr/include

#
#  Uncomment this block of testing -y handling
#
#TCC_OPTS+=      -yTENDRA_BASEDIR=${OBJ_PREFIX} \
#               -yTENDRA_MACHDIR=${OBJ_PREFIX}/lib/machines \
#               -yTENDRA_BINDIR=${OBJ_PREFIX} \
#               -yTENDRA_ENVDIR=${OBJ_PREFIX}/lib/env \
#               -yTENDRA_LIBDIR=${OBJ_PREFIX}/lib \
#               -yTENDRA_INCLDIR=${OBJ_PREFIX}/lib/machines/${BUILD_OS}/80x86/include \
#               -yTENDRA_STARTUPDIR=${OBJ_PREFIX}/lib \
#               -yTENDRA_TMPDIR=/tmp
