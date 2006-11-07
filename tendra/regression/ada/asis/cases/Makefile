# $TenDRA:  $

SRC_DIR =	${.CURDIR:C/(.*)\/regression.*/\1/}
OUT_DIR =	${SRC_DIR}/obj/${NAME}
INCL    =       ${SRC_DIR}/src/lib/libada/spec/
.SUFFIXES:	.${NAME} .${NAME}.out

run: *.${NAME}
	${MAKE} ${.ALLSRC:S/${NAME}/${NAME}.out/g}

.${NAME}.${NAME}.out :
	if [ -f ${.IMPSRC:R}.adb ]; then \
	        GELA_INCLUDE_PATH=${INCL} \
		${OUT_DIR}/${NAME} ${.IMPSRC:R}.adb body ${.IMPSRC:R} \
		>  ${OUT_DIR}/${.TARGET}; \
	else \
	        GELA_INCLUDE_PATH=${INCL} \
		${OUT_DIR}/${NAME} ${.IMPSRC:R}.ads spec ${.IMPSRC:R} \
		>  ${OUT_DIR}/${.TARGET}; \
	fi
	diff ${.IMPSRC} ${OUT_DIR}/${.TARGET}

.include "${.CURDIR}/../test_list.mk"

make-subdir:
.for TEST in ${TESTS}
	${MAKE} run NAME=${TEST}
.endfor 
