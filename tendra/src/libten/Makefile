# $TenDRA$

SHLIB	= libten.a

SRCS=	argparse.c catstd.c char.c cstring.c dstring.c fmm.c msgcat.c ostream.c \
		tdf_bstream tdf_decode.c tdf_encode.c tdf_fstream.c \
		tdf_stream.c tdf_utils.c \
		tenapp.c

CFLAGS	+= -I${.OBJDIR} -I${SRC_DIR}/src/include

DEPEND_SRC= catstd.c

# mkerr needs to be used from the src/* directory, due to it being built after
# libten.

catstd.c catstd.h: catstd.cat
	${BIN_AWK} -f ${SRC_DIR}/src/utilities/mkerr/mkerr.awk -- -n catstdn.h \
		-c ${.OBJDIR}/catstd.c \
		-l ${.OBJDIR}/catstd.h ${.CURDIR}/catstd.cat
		
CLEANFILES += catstd.h catstd.c catstdn.h

.include "${.CURDIR}/../../mk/base/tendra.prog.mk"
