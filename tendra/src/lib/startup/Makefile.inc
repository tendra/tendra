# $TenDRA$

DEPEND_SRC=	${DATA}

${DATA}:
.for i in ${DATA}
	@${CP_VERBOSE} ${.CURDIR}/$i ${.OBJDIR}/$i
.endfor

CLEANFILES=	${DATA}
