# $TenDRA$

DEPEND_SRC=	${DATA}

${DATA}:
.for i in ${DATA}
	@cp -v ${.CURDIR}/$i ${.OBJDIR}/$i
.endfor

CLEANFILES=	${DATA}
