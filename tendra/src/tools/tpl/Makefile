# $Id$

# Standard directories and files
SRC2=${.CURDIR}/templ
SPEC=${BASE}/src/lib/tdf/def_4_0.db

# Standard variables

TCCOPTS=	-Yansi -Xs
CCOPTS=		${TCCOPTS} -I${SRC}
LIBS=

PROG=		tpl

SRCS=		analyse_sort.c consfile.c decodings.c errors.c find_id.c\
		fnsfile.c includes.c lex.c main.c readstreams.c standardsh.c\
		streams.c syntax.c units.c util.c

#MAKE_TDF=make_tdf
#SID?=		${.OBJDIR}/../../utilities/sid/sid
#SIDOPTS=-l ossg-c -s no-lines
#SORT=sort
#
#SID_OUT=${SRC}/syntax.c ${SRC}/syntax.h
#
#GEN_FILES=${SRC}/consfile.c ${SRC}/consfile.h ${SRC}/decodings.c\
# ${SRC}/decodings.h ${SRC}/encodings.h ${SRC}/enc_nos.h ${SRC}/fnsfile.c
#
#${SRC}/syntax.c : ${SRC}/syntax.sid ${SRC}/syntax.act
#	@${REMOVE} ${SID_OUT}
#	${SID} ${SIDOPTS} ${SRC}/syntax.sid ${SRC}/syntax.act ${SID_OUT}
#
#${SRC}/consfile.c : ${SRC2}/consfile.c ${SPEC}
#	@${REMOVE} ${SRC}/consfile.c
#	${MAKE_TDF} ${SPEC} ${SRC2}/consfile.c | ${SORT} > ${SRC}/consfile.c
#
#${SRC}/consfile.h : ${SRC2}/consfile.h ${SPEC}
#	@${REMOVE} ${SRC}/consfile.h
#	${MAKE_TDF} ${SPEC} ${SRC2}/consfile.h ${SRC}/consfile.h
#
#${SRC}/decodings.c : ${SRC2}/decodings.c ${SPEC}
#	@${REMOVE} ${SRC}/decodings.c
#	${MAKE_TDF} ${SPEC} ${SRC2}/decodings.c ${SRC}/decodings.c
#
#${SRC}/decodings.h : ${SRC2}/decodings.h ${SPEC}
#	@${REMOVE} ${SRC}/decodings.h
#	${MAKE_TDF} ${SPEC} ${SRC2}/decodings.h ${SRC}/decodings.h
#
#${SRC}/encodings.h : ${SRC2}/encodings.h ${SPEC}
#	@${REMOVE} ${SRC}/encodings.h
#	${MAKE_TDF} ${SPEC} ${SRC2}/encodings.h ${SRC}/encodings.h
#
#${SRC}/enc_nos.h : ${SRC2}/enc_nos.h ${SPEC}
#	@${REMOVE} ${SRC}/enc_nos.h
#	${MAKE_TDF} ${SPEC} ${SRC2}/enc_nos.h ${SRC}/enc_nos.h
#
#${SRC}/fnsfile.c : ${SRC2}/fnsfile.c ${SPEC}
#	@${REMOVE} ${SRC}/fnsfile.c
#	${MAKE_TDF} ${SPEC} ${SRC2}/fnsfile.c ${SRC}/fnsfile.c

.include "../Makefile.inc"
