# $TenDRA$

INSTALL_MACHINE=	hpux/hppa

.PATH : ${.CURDIR} ${.CURDIR}/tokens ${OBJ_DIR} . ${.CURDIR}/../../common/tokens

# include
DATA_INCLUDE=	include/limits.h include/search.h include/stdarg.h \
		include/varargs.h include/xti.h

# startup
DATA_STARTUP+=	startup/system.h

MAKEDIR=	include startup tokens

DEPEND_SRC=	${DATA_INCLUDE} ${DATA_STARTUP}

${DATA_INCLUDE} ${DATA_STARTUP}:
	@echo ${.CURDIR}/${.TARGET} -> ${OBJ_DIR}/${.TARGET}
	@${BIN_CP} ${ARGS_CP} ${.CURDIR}/${.TARGET} ${OBJ_DIR}/${.TARGET}

CLEANOPT=	-r
CLEANFILES=     ${MAKEDIR}

.include "${.CURDIR}/../../../../../mk/base/tendra.prog.mk"
