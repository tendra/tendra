# $TenDRA$

INSTALL_MACHINE=	osf1/alpha

.PATH : ${.CURDIR} ${.CURDIR}/tokens ${OBJ_DIR} . ${.CURDIR}/../../common/tokens

# include
DATA_INCLUDE=	include/ctype.h include/fnmatch.h include/stdarg.h \
		include/stddef.h include/varargs.h

# include/machine
DATA_INCLUDE+=	include/machine/machlimits.h

# include/sys
DATA_INCLUDE+=	include/sys/param.h include/sys/sem.h

# startup
DATA_STARTUP+=	startup/system.h

MAKEDIR=	include include/machine include/sys startup tokens

DEPEND_SRC=	${DATA_INCLUDE} ${DATA_STARTUP}

${DATA_INCLUDE} ${DATA_STARTUP}:
	@echo ${.CURDIR}/${.TARGET} -> ${OBJ_DIR}/${.TARGET}
	@${BIN_CP} ${ARGS_CP} -R ${.CURDIR}/${.TARGET} ${OBJ_DIR}/${.TARGET}

CLEANOPT=	-r
CLEANFILES=     ${MAKEDIR}

.include "${.CURDIR}/../../../../../mk/base/tendra.prog.mk"
