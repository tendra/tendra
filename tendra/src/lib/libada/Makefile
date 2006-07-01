# $TenDRA:  $

.if !defined(SRC_DIR)
SRC_DIR=        ${.CURDIR:C/(.*)\/src.*/\1/}
.endif

.if exists (${SRC_DIR}/config.mk)
.include "${SRC_DIR}/config.mk"
.endif


.if defined(WITH_ADA)

STANDARD_DIR=		include/ada/standard
INSTALL_TARGETS=	install-standard
INSTALL_SUB=		${STANDARD_DIR}

install-standard:
	${BIN_CP} ${.CURDIR}/spec/*.ads ${INSTALL_PREFIX}/${STANDARD_DIR}
	${BIN_CHMOD} 644 ${INSTALL_PREFIX}/${STANDARD_DIR}/*.ads

.include "${.CURDIR}/../../../mk/base/tendra.prog.mk"

.else

install:

make-subdir:

clean:

.endif
