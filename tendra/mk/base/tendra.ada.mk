# $TenDRA: tendra.ada.mk  $

ADA_SRC?= ${ADA_PROG}.adb

${ADA_PROG}: ${DEPEND_SRC}
	pwd
	${BIN_ECHO} tendra.ada.mk  ${ADA_MAIN} => ${ADA_PROG}
	${BIN_GNATMAKE} ${CFLAGS} -o ${.TARGET} ${ADA_SRC} -largs ${LDFLAGS}

${ADA_LIB}: ${DEPEND_SRC}
	@${BIN_ECHO} "SRC:" ${.ALLSRC}
	${BIN_GNATMAKE} ${CFLAGS} ${ADA_SRC}
	${BIN_AR} cr ${.TARGET} *.o

