# $TenDRA$

DEPEND_SRC=	${DATA}

${DATA}:
.for i in ${DATA}
	@${CP} ${CP_ARGS} ${.CURDIR}/$i ${.OBJDIR}/$i
.endfor

CLEANFILES=	${DATA}
