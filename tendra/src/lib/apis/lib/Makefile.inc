# $TenDRA$
#
# This include is only for building the libraries.

#.PATH : ${.OBJDIR}.api  /mnt/free/tendra/new/obj/lib/apis/lib

TLD_FLAGS+=	-mc

TCC_OPTS+=      -yTENDRA_BASEDIR=${SRC_DIR}/obj/

TCC_OPTS+=	-Fj \
		-Y${DEFAULT_BUILD} \
		-Ybuilding \
		-Y32bit

TCCFLAGS+=	-I${OBJ_PREFIX}/lib/machines/${BUILD_OS}/${MACH_CPU}/include \
		-I/usr/include

#
#  Uncomment this block of testing -y handling
#
#TCC_OPTS+=      -yTENDRA_BASEDIR=${SRC_DIR}/obj \
#               -yTENDRA_MACHDIR=${SRC_DIR}/obj/lib/machines \
#               -yTENDRA_BINDIR=${SRC_DIR}/obj \
#               -yTENDRA_ENVDIR=${SRC_DIR}/obj/lib/env \
#               -yTENDRA_LIBDIR=${SRC_DIR}/obj/lib \
#               -yTENDRA_INCLDIR=${SRC_DIR}/obj/lib/machines/${BUILD_OS}/80x86/include \
#               -yTENDRA_STARTUPDIR=${SRC_DIR}/obj/lib \
#               -yTENDRA_TMPDIR=/tmp
