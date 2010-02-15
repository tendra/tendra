# $Id$

DEST=${OBJ_DIR}/src/lib
#SRC=${BASE}/src/tools/tspec
API_DIR=${BASE_DIR}/src/lib/apis

#LEXI=lexi
#SID=sid
#SIDOPTS=-l ossg-c -s no-lines
#
#SID_OUT=${SRC}/syntax.c ${SRC}/syntax.h
#LEXI_OUT=${SRC}/lexer.h ${SRC}/keyword.h
#
#auto : ${SID_OUT} ${LEXI_OUT}
#
#${SRC}/syntax.c : ${SRC}/syntax.sid ${SRC}/syntax.act
#	@${REMOVE} ${SID_OUT}
#	${SID} ${SIDOPTS} ${SRC}/syntax.sid ${SRC}/syntax.act ${SID_OUT}
#
#${SRC}/lexer.h : ${SRC}/lexer.lxi
#	@${REMOVE} ${SRC}/lexer.h
#	${LEXI} ${SRC}/lexer.lxi ${SRC}/lexer.h
#
#${SRC}/keyword.h : ${SRC}/lexer.lxi
#	@${REMOVE} ${SRC}/keyword.h
#	${LEXI} -k ${SRC}/lexer.lxi ${SRC}/keyword.h
#
#auto_clobber :
#	${REMOVE} ${SID_OUT} ${LEXI_OUT}

.include "Makefile.inc"


TCCOPTS=	-Yposix1 -Xs
CCOPTS=		-I${BASE_DIR}/${INCLUDE} -I${.CURDIR}

SRCS+=	hash.c
SRCS+=	index.c
SRCS+=	lex.c
SRCS+=	main.c
SRCS+=	makefile.c
SRCS+=	name.c
SRCS+=	object.c
SRCS+=	print.c
SRCS+=	syntax.c
SRCS+=	type.c
SRCS+=	utility.c
SRCS+=	variable.c

.include <tendra.obj.mk>


PROG=		${.CURDIR:T}
WRAPPER=	${.CURDIR:T}.sh

.include <tendra.prog.mk>

