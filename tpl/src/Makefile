# $Id$

.include "Makefile.inc"

# TODO: move templ/-generated stuff into obj_c/obj_tok, as for the others

PARTS+=	src/shared

.include <tendra.partial.mk>


SRCS+=	analyse_sort.c
SRCS+=	consfile.c
SRCS+=	decodings.c
SRCS+=	errors.c
SRCS+=	find_id.c
SRCS+=	fnsfile.c
SRCS+=	includes.c
SRCS+=	lex.c
SRCS+=	main.c
SRCS+=	readstreams.c
SRCS+=	standardsh.c
SRCS+=	streams.c
SRCS+=	syntax.c
SRCS+=	units.c
SRCS+=	util.c

.include <tendra.obj.mk>


PROG=	tpl

.include <tendra.prog.mk>


SIDOPTS+=	-s unreachable-macro

SYNTAX+=	syntax.sid

.include <tendra.sid.mk>


#SPEC=${BASE_DIR}/src/lib/tdf/def_4_0.db

#MAKE_TDF=make_tdf
#SORT=sort
#
#SID_OUT=${SRC}/syntax.c ${SRC}/syntax.h
#
#GEN_FILES=${SRC}/consfile.c ${SRC}/consfile.h ${SRC}/decodings.c\
# ${SRC}/decodings.h ${SRC}/encodings.h ${SRC}/enc_nos.h ${SRC}/fnsfile.c
#
#consfile.c : ${TEMPL}/consfile.c ${SPEC}
#	@${RMFILE} ${.TARGET}
#	${MAKE_TDF} ${SPEC} ${TEMPL}/consfile.c |\
#		${SORT} > ${.CURDIR}/${.TARGET}
#
#consfile.h : ${TEMPL}/consfile.h ${SPEC}
#	@${RMFILE} ${.TARGET}
#	${MAKE_TDF} ${SPEC} ${TEMPL}/consfile.h ${.CURDIR}/${.TARGET}
#
#decodings.c : ${TEMPL}/decodings.c ${SPEC}
#	@${RMFILE} ${.TARGET}
#	${MAKE_TDF} ${SPEC} ${TEMPL}/decodings.c ${.CURDIR}/${.TARGET}
#
#decodings.h : ${TEMPL}/decodings.h ${SPEC}
#	@${RMFILE} ${.TARGET}
#	${MAKE_TDF} ${SPEC} ${TEMPL}/decodings.h ${.CURDIR}/${.TARGET}
#
#encodings.h : ${TEMPL}/encodings.h ${SPEC}
#	@${RMFILE} ${.TARGET}
#	${MAKE_TDF} ${SPEC} ${TEMPL}/encodings.h ${.CURDIR}/${.TARGET}
#
#enc_nos.h : ${TEMPL}/enc_nos.h ${SPEC}
#	@${RMFILE} ${.TARGET}
#	${MAKE_TDF} ${SPEC} ${TEMPL}/enc_nos.h ${.CURDIR}/${.TARGET}
#
#fnsfile.c : ${TEMPL}/fnsfile.c ${SPEC}
#	@${RMFILE} ${.TARGET}
#	${MAKE_TDF} ${SPEC} ${TEMPL}/fnsfile.c ${.CURDIR}/${.TARGET}

