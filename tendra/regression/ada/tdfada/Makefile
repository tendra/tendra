# $TenDRA:  $
#
# This is temporary version of makefile. It requires installed tcc.
#

SRC_DIR =	${.CURDIR:C/(.*)\/regression.*/\1/}
TDFADA =	${SRC_DIR}/obj/producers/ada/tdfada/tdfada

.SUFFIXES:	.adb .out
.MAIN: make-subdir

run: *.${NAME}
	${MAKE} ${.ALLSRC:S/${NAME}/${NAME}.out/g}

.adb.out :
	${TDFADA} ${.IMPSRC}
	tcc -DAda_Main=${.IMPSRC:C/b(.*).adb/B\1/} wrapper.c ${.IMPSRC:R}.j
	./a.out

make-subdir: b????.adb
	${MAKE} ${.ALLSRC:S/.adb/.out/g}
