# $TenDRA$

CAT_STD?=	${SRC_DIR}/src/libten/catstd.cat

# Added flags
LDFLAGS+=       -L${OBJ_PREFIX}/libten
LDADD +=        -lten

# Added srcs
SRCS+=	catstd.c

# Dependancies
DEPEND_SRC+=	catstd.c

# Target
catstd.c:: messages.cat ${CAT_EXTRA}
	${BIN_AWK} -f ${MKERR} -- \
		-c ${.OBJDIR}/catstd.c  -l ${.OBJDIR}/catstd.h \
		${CAT_STD} ${.CURDIR}/messages.cat ${CAT_EXTRA}


CLEANFILES+=	catstd.h catstd.c
