# $TenDRA$

.SUFFIXES:	.awk
SED_OPTS=	-e "s|@BIN_AWK@|${BIN_AWK}|g"

MKERR_SRC=	mkerr.awk

DEPEND_SRC=	${MKERR_SRC:R}

.awk:
	${BIN_CAT} ${.IMPSRC} \
	|${BIN_SED} ${SED_OPTS} \
	> ${.OBJDIR}/${.TARGET}


CLEANFILES=	${MKERR_SRC:R}

.include "${.CURDIR}/../../../mk/base/tendra.prog.mk"
