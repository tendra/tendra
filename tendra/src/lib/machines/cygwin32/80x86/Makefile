# $TenDRA: Makefile 2282 2005-11-06 10:13:06Z stefanf $

INSTALL_MACHINE=	cygwin32/80x86

.PATH : ${.CURDIR} ${.CURDIR}/tokens ${OBJ_DIR} . ${.CURDIR}/../../common/tokens

# include
DATA_INCLUDE=	include/alloca.h include/ctype.h include/float.h\
		include/limits.h include/locale.h include/math.h\
		include/setjmp.h include/stdarg.h include/stddef.h\
		include/stdio.h include/unistd.h include/varargs.h

# include/sys
DATA_INCLUDE+=	include/sys/wait.h include/sys/_types.h\
		include/sys/dirent.h include/sys/resource.h

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
