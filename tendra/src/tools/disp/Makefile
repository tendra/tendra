# $TenDRA$

CFLAGS+= -I${.CURDIR} -I${SRC_DIR}/src/include -I. 
.PATH : ${.CURDIR} ${.CURDIR}/templ .
SID_OPTS=	-l ossg-c -s no-lines


PROG = disp

SRCS=	basic.c binding.c capsule.c file.c main.c pretty.c \
	sort.c tdf.c tree.c unit.c utility.c

DEPEND_SRC=	tdf.c tdf.h

#tdf.c: tdf.c-tdf
#	${MAKE_TDF} ${.CURDIR}/../../lib/tdf/def_4_1.db ${.IMPSRC} |\
#	${SED} -f ${.CURDIR}/templ/tdf.sed > ${OBJ_DIR}/${.TARGET}

CLEANFILES+=	tdf.c tdf.h

.include "${.CURDIR}/../../../mk/base/tendra.prog.mk"
