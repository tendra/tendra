# $TenDRA$

SUBDIR= startup apis machines

.include "${.CURDIR}/../../mk/base/tendra.subdir.mk"
# $TenDRA$

SUBDIR=	${BUILD_OS}/common/${MACH_CPU}

.if exists(${BUILD_OS}/${MACH_VERS})
SUBDIR+=${BUILD_OS}/${MACH_VERS}
.endif

.include "${.CURDIR}/../../mk/base/tendra.subdir.mk"
