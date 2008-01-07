# $TenDRA$

CAT_STD?=	${SRC_DIR}/src/libten/catstd.cat

# Added flags
LDFLAGS+=       -L${OBJ_PREFIX}/libten
LDADD +=        -lten

# Added srcs
SRCS+=	catstd.c

# Dependancies
DEPEND_SRC+=	catstd.c

# Productions
CAT_PRODS+=	-c ${.OBJDIR}/catstd.c -l ${.OBJDIR}/catstd.h \
	-n ${.OBJDIR}/catstdn.h

# Target
catstd.c:: messages.cat ${CAT_EXTRA}
	${BIN_AWK} -f ${MKERR} -- \
		${CAT_PRODS} \
		${CAT_STD} ${.CURDIR}/messages.cat ${CAT_EXTRA}


CLEANFILES+=	catstd.h catstdn.h catstd.c
