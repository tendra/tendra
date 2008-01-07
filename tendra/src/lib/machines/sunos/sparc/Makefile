# $TenDRA$

INSTALL_MACHINE=	sunos/sparc

.PATH : ${.CURDIR} ${.CURDIR}/tokens ${OBJ_DIR} . ${.CURDIR}/../../common/tokens

# include
DATA_INCLUDE=	include/ctype.h include/limits.h include/stdarg.h \
		include/unistd.h include/xti.h 

# include/sys
#DATA_INCLUDE+=	include/sys/param.h include/sys/shm.h

# startup
DATA_STARTUP+=	startup/system.h

MAKEDIR=	include include/sys startup tokens

DEPEND_SRC=	${DATA_INCLUDE} ${DATA_STARTUP}

${DATA_INCLUDE} ${DATA_STARTUP}:
	@echo ${.CURDIR}/${.TARGET} -> ${OBJ_DIR}/${.TARGET}
	@${BIN_CP} ${ARGS_CP} -R ${.CURDIR}/${.TARGET} ${OBJ_DIR}/${.TARGET}

CLEANOPT=	-r
CLEANFILES=     ${MAKEDIR}

.include "${.CURDIR}/../../../../../mk/base/tendra.prog.mk"
