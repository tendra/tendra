# $TenDRA$

IMACHINE=	cygwin32/80x86

.PATH : ${.CURDIR} ${.CURDIR}/tokens ${OBJ_DIR} . ${.CURDIR}/../../common/tokens

# include
DATA_INCLUDE=	include/alloca.h include/ctype.h include/float.h\
		include/limits.h include/locale.h include/math.h\
		include/setjmp.h include/stdarg.h include/stddef.h\
		include/stdio.h include/unistd.h include/varargs.h

# include/sys
DATA_INCLUDE+=	include/sys/wait.h

# startup
DATA_STARTUP+=	startup/ansi.h startup/bsd_extn.h startup/cpp.h startup/gcc.h \
		startup/iso.h startup/posix.h startup/posix1.h \
		startup/posix2.h startup/svid3.h startup/system.h \
		startup/unix95.h startup/xpg3.h startup/xpg4.h 

MAKEDIR=	include include/sys startup tokens

DEPEND_SRC=	${DATA_INCLUDE} ${DATA_STARTUP}

${DATA_INCLUDE} ${DATA_STARTUP}:
	@echo ${.CURDIR}/${.TARGET} -> ${OBJ_DIR}/${.TARGET}
	@${CP_VERBOSE} -R ${.CURDIR}/${.TARGET} ${OBJ_DIR}/${.TARGET}

CLEANOPT=	-r
CLEANFILES=     ${MAKEDIR}

.include "${.CURDIR}/../../../../../mk/base/tendra.prog.mk"
