# $TenDRA$

INSTALL_MACHINE=	sunos/sparc

.PATH : ${.CURDIR} ${.CURDIR}/tokens ${OBJ_DIR} . ${.CURDIR}/../../common/tokens

# include
DATA_INCLUDE=	include/ctype.h include/limits.h include/stdarg.h \
		include/unistd.h include/xti.h 

# include/sys
#DATA_INCLUDE+=	include/sys/param.h include/sys/shm.h

# startup
DATA_STARTUP+=	startup/ansi.h startup/bsd_extn.h startup/cpp.h startup/gcc.h \
		startup/iso.h startup/iso99.h startup/posix.h startup/posix1.h \
		startup/posix2.h startup/svid3.h startup/system.h \
		startup/unix95.h startup/xpg3.h startup/xpg4.h 

MAKEDIR=	include include/sys startup tokens

DEPEND_SRC=	${DATA_INCLUDE} ${DATA_STARTUP}

${DATA_INCLUDE} ${DATA_STARTUP}:
	@echo ${.CURDIR}/${.TARGET} -> ${OBJ_DIR}/${.TARGET}
	@${BIN_CP} ${ARGS_CP} -R ${.CURDIR}/${.TARGET} ${OBJ_DIR}/${.TARGET}

CLEANOPT=	-r
CLEANFILES=     ${MAKEDIR}

.include "${.CURDIR}/../../../../../mk/base/tendra.prog.mk"
