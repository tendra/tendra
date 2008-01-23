# $TenDRA: tendra.ada.mk  $

ADA_SRC?= ${ADA_PROG}.adb

${ADA_PROG}: ${DEPEND_SRC}
	${BIN_GNATMAKE} ${CFLAGS} ${ADA_FLAGS} -o ${.TARGET} ${ADA_SRC} -largs ${LDFLAGS}

${ADA_LIB}: ${DEPEND_SRC}
	${BIN_GNATMAKE} ${CFLAGS} ${ADA_FLAGS} ${ADA_SRC}
	${BIN_AR} cr ${.TARGET} *.o

