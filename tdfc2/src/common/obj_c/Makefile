# $Id$

#${SRC2}/c_class.h : ${ALG} ${TEMPL}
#   @${RMFILE} ${SRC2}/*.h
#   ${CALCULUS} -a -x ${ALG} ${SRC2}
#   ${CALCULUS} ${ALG} -T${SRC2B}/bits.h ${SRC2}/bits.h
#   ${CALCULUS} ${ALG} -T${SRC2B}/err_ext.h ${SRC2}/err_ext.h
#   ${CALCULUS} ${ALG} -T${SRC2B}/loc_ext.h ${SRC2}/loc_ext.h
#
#${SRC2A}/c_class.h : ${ALG} ${TEMPL}
#   @${RMFILE} ${SRC2A}/*.h
#   ${CALCULUS} -a -x -t ${ALG} ${SRC2A}
#   ${CALCULUS} -t ${ALG} -T${SRC2B}/bits.h ${SRC2A}/bits.h
#   ${CALCULUS} -t ${ALG} -T${SRC2B}/err_ext.h ${SRC2A}/err_ext.h
#   ${CALCULUS} -t ${ALG} -T${SRC2B}/loc_ext.h ${SRC2A}/loc_ext.h

.include "Makefile.inc"


CCOPTS+=	-I ../../common
CCOPTS+=	-I ../utility
CCOPTS+=	-I .

SRCS+=	c_class.c

.include <tendra.obj.mk>

.include <tendra.partial.mk>

