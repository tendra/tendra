# $Id$

# Standard directories and files
SRCC=${.CURDIR}/../../common
SRC1=${.CURDIR}/../common
SRC2=${SRCC}/construct
SRC3=${SRCC}/diag
SRC4=${SRCC}/linkinfo
SRC5=${SRCC}/reader
SRC6=${SRCC}/templ
SPEC=${BASE}/src/lib/tdf/def_4_1.db

# Standard variables

TCCOPTS=-Xc -Y32bit -Yansi
CCOPTS=	${TCCOPTS} -I${BASE_DIR}/${INCLUDE} -I${.CURDIR} -I${SRCC} -I${SRC1}\
	-I${SRC2} -I${SRC3} -I${SRC4} -I${SRC5}
LIBS=

# Dependencies and construction rules

PROG=	trans

SRCS=	aldefs.o basicread.o case_opt.o check.o check_id.o codehere.o\
	comment.o complex_eq.o const.o decoder.o dg_aux.o dg_fns.o diag_fns.o\
	diag_info.o dw2_extra.o eval.o exp.o f64.o flags.o flpt.o flpt_fns.o\
	foralls.o getregs.o global_opt.o glopt.o guard.o inl_norm.o inline.o\
	inlinechoice.o inst_fmt.o install_fns.o installglob.o is_worth.o\
	label_ops.o labels.o li_fns.o locate.o machine.o machine_toks.o\
	makecode.o mark_scope.o me_fns.o misc_c.o move.o muldvrem.o needscan.o\
	oprators.o proc.o read_fns.o read_sort.o readglob.o regable.o\
	regalloc.o regexps.o sparcdiags.o sparcins.o sparctrans.o spec_tok.o\
	special.o table_fns.o tempdecs.o translat.o unroll.o weights.o xalloc.o

.PATH:	${SRC1} ${SRC2} ${SRC3} ${SRC4} ${SRC5} ${SRC6}

#MAKE_TDF=make_tdf
#REMOVE=rm -f
#
#TDF_OUT=${SRC5}/decoder.c ${SRC5}/ecodes.h ${SRC5}/externs.h ${SRC5}/inits.h\
# ${SRC5}/main_reads.h ${SRC5}/temp_fns.new
#
#auto : ${TDF_OUT}
#
#${SRC5}/decoder.c : ${SPEC} ${SRC6}/decoder.c
#	@${REMOVE} ${SRC5}/decoder.c
#	${MAKE_TDF} ${SPEC} ${SRC6}/decoder.c ${SRC5}/decoder.c
#
#${SRC5}/ecodes.h : ${SPEC} ${SRC6}/ecodes.h
#	@${REMOVE} ${SRC5}/ecodes.h
#	${MAKE_TDF} ${SPEC} ${SRC6}/ecodes.h ${SRC5}/ecodes.h
#
#${SRC5}/externs.h : ${SPEC} ${SRC6}/externs.h
#	@${REMOVE} ${SRC5}/externs.h
#	${MAKE_TDF} ${SPEC} ${SRC6}/externs.h ${SRC5}/externs.h
#
#${SRC5}/inits.h : ${SPEC} ${SRC6}/inits.h
#	@${REMOVE} ${SRC5}/inits.h
#	${MAKE_TDF} ${SPEC} ${SRC6}/inits.h ${SRC5}/inits.h
#
#${SRC5}/main_reads.h : ${SPEC} ${SRC6}/main_reads.h
#	@${REMOVE} ${SRC5}/main_reads.h
#	${MAKE_TDF} ${SPEC} ${SRC6}/main_reads.h ${SRC5}/main_reads.h
#
#${SRC5}/temp_fns.new : ${SPEC} ${SRC6}/temp_fns.c
#	@${REMOVE} ${SRC5}/temp_fns.new
#	${MAKE_TDF} ${SPEC} ${SRC6}/temp_fns.c ${SRC5}/temp_fns.new
#
#auto_clobber :
#	${REMOVE} ${TDF_OUT}

.include "../Makefile.inc"
