# $Id$

.include "Makefile.inc"


PART_CFLAGS+=	-I ${.CURDIR}/shared

PARTS+=	src/shared/error
PARTS+=	src/shared/xalloc

.include <tendra.partial.mk>


CCOPTS+=	-I shared

SRCS+=	basic.c
SRCS+=	binding.c
SRCS+=	capsule.c
SRCS+=	file.c
SRCS+=	main.c
SRCS+=	pretty.c
SRCS+=	sort.c
SRCS+=	tdf.c
SRCS+=	tree.c
SRCS+=	unit.c
SRCS+=	utility.c

.include <tendra.obj.mk>


PROG=	disp

.include <tendra.prog.mk>


#MAKE_TDF=make_tdf
#SED=sed
#
#auto : ${SRC}/tdf.c ${SRC}/tdf.h
#
#${SRC}/tdf.c : ${SPEC} ${SRC1}/tdf.c ${SRC1}/tdf.sed
#	@${REMOVE} ${SRC}/tdf.c
#	${MAKE_TDF} ${SPEC} ${SRC1}/tdf.c | ${SED} -f ${SRC1}/tdf.sed > ${SRC}/tdf.c
#
#${SRC}/tdf.h : ${SPEC} ${SRC1}/tdf.h
#	@${REMOVE} ${SRC}/tdf.h
#	${MAKE_TDF} ${SPEC} ${SRC1}/tdf.h ${SRC}/tdf.h
#
#auto_clobber :
#	${REMOVE} ${SRC}/tdf.c ${SRC}/tdf.h

