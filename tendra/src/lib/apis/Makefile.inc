# $TenDRA$

DEPEND_SRC=	${API}
OBJ_TMP=	${OBJ_DIR:C/${API}//}

${API}:
	${TSPEC} ${TSPEC_FLAGS} -w -v -O${OBJ_TMP} -S${OBJ_TMP} \
		-I${.CURDIR}/.. ${API}

.include "../../../mk/base/tendra.prog.mk"

