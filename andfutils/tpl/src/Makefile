# $Id$

#TEMPL=templ

REMOVE=rm -f

TARGETS=analyse_sort.o consfile.o decodings.o errors.o find_id.o \
		fnsfile.o includes.o lex.o main.o readstreams.o standardsh.o \
		streams.o syntax.o units.o util.o

all: tpl

tpl: $(TARGETS)
	$(CC) -o tpl $(TARGETS)

clean:
	$(REMOVE) tpl $(TARGETS)

#SPEC=${BASE_DIR}/src/lib/tdf/def_4_0.db

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
#consfile.c : ${TEMPL}/consfile.c ${SPEC}
#	@${REMOVE} ${.TARGET}
#	${MAKE_TDF} ${SPEC} ${TEMPL}/consfile.c |\
#		${SORT} > ${.CURDIR}/${.TARGET}
#
#consfile.h : ${TEMPL}/consfile.h ${SPEC}
#	@${REMOVE} ${.TARGET}
#	${MAKE_TDF} ${SPEC} ${TEMPL}/consfile.h ${.CURDIR}/${.TARGET}
#
#decodings.c : ${TEMPL}/decodings.c ${SPEC}
#	@${REMOVE} ${.TARGET}
#	${MAKE_TDF} ${SPEC} ${TEMPL}/decodings.c ${.CURDIR}/${.TARGET}
#
#decodings.h : ${TEMPL}/decodings.h ${SPEC}
#	@${REMOVE} ${.TARGET}
#	${MAKE_TDF} ${SPEC} ${TEMPL}/decodings.h ${.CURDIR}/${.TARGET}
#
#encodings.h : ${TEMPL}/encodings.h ${SPEC}
#	@${REMOVE} ${.TARGET}
#	${MAKE_TDF} ${SPEC} ${TEMPL}/encodings.h ${.CURDIR}/${.TARGET}
#
#enc_nos.h : ${TEMPL}/enc_nos.h ${SPEC}
#	@${REMOVE} ${.TARGET}
#	${MAKE_TDF} ${SPEC} ${TEMPL}/enc_nos.h ${.CURDIR}/${.TARGET}
#
#fnsfile.c : ${TEMPL}/fnsfile.c ${SPEC}
#	@${REMOVE} ${.TARGET}
#	${MAKE_TDF} ${SPEC} ${TEMPL}/fnsfile.c ${.CURDIR}/${.TARGET}
