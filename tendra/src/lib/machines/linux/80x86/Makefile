# $TenDRA$

INSTALL_MACHINE=	linux/80x86

.PATH : ${.CURDIR} ${OBJ_DIR}/tokens

# include
DATA_INCLUDE=	include/alloca.h include/ctype.h include/float.h \
		include/gconv.h \
		include/langinfo.h include/limits.h include/math.h \
		include/nl_types.h include/stdarg.h include/stddef.h \
		include/ulimit.h include/unistd.h include/varargs.h \
		include/xti.h

# include/asm
DATA_INCLUDE+=	include/asm/bitops.h

# include/gnu
DATA_INCLUDE+=	include/gnu/types.h

# include/linux
DATA_INCLUDE+=	include/linux/signal.h

# include/sys
DATA_INCLUDE+=	include/sys/msg.h include/sys/sem.h include/sys/shm.h \
		include/sys/types.h

# startup
DATA_STARTUP+=	startup/system.h

MAKEDIR=	include include/asm include/gnu include/linux include/sys \
		startup tokens

DEPEND_SRC=	${DATA_INCLUDE} ${DATA_STARTUP}

${DATA_INCLUDE} ${DATA_STARTUP}:
	@${BIN_CP} ${ARGS_CP} -R ${.CURDIR}/${.TARGET} ${OBJ_DIR}/${.TARGET}

CLEANOPT=	-r
CLEANFILES=     ${MAKEDIR}

.include "${.CURDIR}/../../../../../mk/base/tendra.prog.mk"
