# $TenDRA$
#
# This include is only for building the libraries.

.PATH : ${.OBJDIR}.api

TCC_OPTS+=	-Fj \
		-Y${OBJ_PREFIX}/lib/env/freebsd/common/80x86/building \
		-Y${OBJ_PREFIX}/lib/env/freebsd/common/80x86/32bit

TCCFLAGS+=	-I${OBJ_PREFIX}/lib/machines/${BUILD_OS}/${MACH_CPU}/include \
		-Y${OBJ_PREFIX}/lib/env/freebsd/common/80x86/default-build \
		-I/usr/include \
		-I.
