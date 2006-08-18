# $TenDRA:  $
#
# This is temporary version of makefile. It requires installed tcc.
#

SRC_DIR =	${.CURDIR:C/(.*)\/regression.*/\1/}
OBJ_DIR =	${SRC_DIR}/obj/regression/tdfada
TDFADA =	${SRC_DIR}/obj/producers/ada/tdfada/tdfada
INCL =		${SRC_DIR}/obj/producers/ada/tdfada/lib

.include "${SRC_DIR}/config.mk"

.SUFFIXES:	.adb .ads .exe .out .c .pl .j
.PATH.ads:	${.CURDIR} ${INCL}
.PATH.pl:       ${SRC_DIR}/src/lib/libada/token
.MAIN: make-subdir

.if defined(NAME)
DEPEND != test ! -f ${NAME} || grep "Dependencies::" ${NAME} |sed -e "s/.*:://"
.endif

run:
	tcc -M -Ytarget_tok -o ${NAME:.adb=.exe} ${LIST}
	./${NAME:.adb=.exe}
	@rm ${LIST} ${NAME:.adb=.exe}

depend: ${NAME} ${DEPEND} wrapper.c ada.j
	${MAKE} ${.ALLSRC:C/\..*/.j/}
	${MAKE} run LIST="${.ALLSRC:C/\..*/.j/}"

.adb.out :
	${MAKE} depend NAME=${.IMPSRC}

.c.j :
	tcc -Fj -DAda_Main=${NAME:C/b(.*).adb/B\1/} ${.IMPSRC}

ada.j: ada.pl
	tcc -Fj -Ypl_tdf ${.ALLSRC}

.ads.j:
	${TDFADA} ${.IMPSRC}

.adb.j:
	${TDFADA} ${.IMPSRC}

make-subdir: obj-dir all-tests

all-tests: b????.adb
	${MAKE} ${.ALLSRC:S/.adb/.out/g}

obj-dir:
	@if ! test -d ${OBJ_DIR}/; then \
		${BIN_MKDIR} ${ARGS_MKDIR} ${OBJ_DIR}; \
		if ! test -d ${OBJ_DIR}/; then \
			${BIN_ECHO} "Unable to create ${OBJ_DIR}."; \
			exit 1; \
		fi; \
		${BIN_ECHO} "${OBJ_DIR} created for ${.CURDIR}"; \
	fi
