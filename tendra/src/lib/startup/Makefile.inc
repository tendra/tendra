# $TenDRA$

DEPEND_SRC=	${DATA}

${DATA}:
.for i in ${DATA}
	@${BIN_CP} ${ARGS_CP} ${.CURDIR}/$i ${.OBJDIR}/$i
.endfor

CLEANFILES=	${DATA}
