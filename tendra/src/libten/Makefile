# $TenDRA$

SHLIB	= libten.a

SRCS	= catstd.c cstring.c fmm.c msgcat.c ostream.c tenapp.c

CFLAGS	+= -I${.OBJDIR} -I${SRC_DIR}/src/include

DEPEND_SRC= catstd.c

catstd.c catstd.h: catstd.cat
	${BIN_AWK} -f ${.CURDIR}/../utilities/mkerr/mkerr.awk -- -n catstdn.h \
		-c ${.OBJDIR}/catstd.c \
		-l ${.OBJDIR}/catstd.h ${.CURDIR}/catstd.cat
		
CLEANFILES += catstd.h catstd.c catstdn.h

.include "${.CURDIR}/../../mk/base/tendra.prog.mk"
