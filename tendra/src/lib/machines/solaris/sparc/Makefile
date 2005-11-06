# $TenDRA$


CFLAGS+= -Xa
.PATH : ${.CURDIR} ${.CURDIR}/tokens ${OBJ_DIR} . ${.CURDIR}/../../common/tokens

INSTALL_MACHINE=	solaris/sparc

# include
DATA_INCLUDE=	include/limits.h include/stdarg.h include/varargs.h \
		include/wchar.h include/xti.h


# include/sys
DATA_INCLUDE+=	include/sys/msg.h include/sys/shm.h include/sys/socket.h

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

