# $Id$

# Standard directories and files
DEST=${BASE_DIR}/src/lib
INCL_DIR=${DEST}/include
#SRC_DIR=${DEST}/building
#SRC=${BASE}/src/tools/tspec
API_DIR=${BASE_DIR}/src/lib/apis

.PATH=${.CURDIR}

# Standard variables

CC?=		tcc
TCCOPTS=	-Yposix1 -Xs
CCOPTS=		${TCCOPTS} -I${.CURDIR} -DINPUT_DIR=\"${API_DIR}\"\
		 -DINCLUDE_DIR=\"${INCL_DIR}\" -DSRC_DIR=\"${SRC_DIR}\"
LIBS=

# Dependencies and construction rules

PROG=		tspec

SRCS=		hash.c index.c lex.c main.c makefile.c name.c object.c print.c\
		syntax.c type.c utility.c variable.c

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

.include "../Makefile.inc"
