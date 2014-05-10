# $Id$

#TDF_OUT=${SRC6}/decoder.c ${SRC6}/ecodes.h ${SRC6}/externs.h ${SRC6}/inits.h\
# ${SRC6}/main_reads.h ${SRC6}/temp_fns.new
#
#${SRC6}/decoder.c : ${SPEC} ${SRC7}/decoder.c
#   @${RMFILE} ${SRC6}/decoder.c
#   ${MAKE_TDF} ${SPEC} ${SRC7}/decoder.c ${SRC6}/decoder.c
#
#${SRC6}/ecodes.h : ${SPEC} ${SRC7}/ecodes.h
#   @${RMFILE} ${SRC6}/ecodes.h
#   ${MAKE_TDF} ${SPEC} ${SRC7}/ecodes.h ${SRC6}/ecodes.h
#
#${SRC6}/externs.h : ${SPEC} ${SRC7}/externs.h
#   @${RMFILE} ${SRC6}/externs.h
#   ${MAKE_TDF} ${SPEC} ${SRC7}/externs.h ${SRC6}/externs.h
#
#${SRC6}/inits.h : ${SPEC} ${SRC7}/inits.h
#   @${RMFILE} ${SRC6}/inits.h
#   ${MAKE_TDF} ${SPEC} ${SRC7}/inits.h ${SRC6}/inits.h
#
#${SRC6}/main_reads.h : ${SPEC} ${SRC7}/main_reads.h
#   @${RMFILE} ${SRC6}/main_reads.h
#   ${MAKE_TDF} ${SPEC} ${SRC7}/main_reads.h ${SRC6}/main_reads.h
#
#${SRC6}/temp_fns.new : ${SPEC} ${SRC7}/temp_fns.c
#   @${RMFILE} ${SRC6}/temp_fns.new
#   ${MAKE_TDF} ${SPEC} ${SRC7}/temp_fns.c ${SRC6}/temp_fns.new

#TCCOPTS=-Xc -Y32bit -Yc89

.include "Makefile.inc"


CCOPTS+=	-I ..
CCOPTS+=	-I .

SRCS+=	basicread.c
SRCS+=	decoder.c
SRCS+=	read_fns.c
SRCS+=	read_sort.c
SRCS+=	readglob.c
SRCS+=	table_fns.c

.include <tendra.obj.mk>

.include <tendra.partial.mk>

