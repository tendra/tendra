# $Id$

# Standard directories and files
SRCC=${.CURDIR}/../../common
SRC1=${.CURDIR}/../common
SRC2=${SRCC}/construct
SRC3=${SRCC}/diag
SRC4=${SRCC}/dwarf2
SRC5=${SRCC}/linkinfo
SRC6=${SRCC}/reader
SRC7=${SRCC}/templ
SPEC=${BASE}/src/lib/tdf/def_4_1.db

# Standard variables

TCCOPTS=-Xc -Y32bit -Yansi
CCOPTS=	${TCCOPTS} -I${BASE_DIR}/${INCLUDE} -I${.CURDIR} -I${SRCC} -I${SRC1}\
	-I${SRC2} -I${SRC3} -I${SRC4} -I${SRC5} -I${SRC6}
LIBS=

# Dependencies and construction rules

PROG=	trans

SRCS=	aldefs.c basicread.c case_opt.c check.c check_id.c codehere.c\
	comment.c complex_eq.c const.c decoder.c dg_aux.c dg_fns.c diag_fns.c\
	diag_info.c dw2_abbrev.c dw2_basic.c dw2_common.c dw2_config.c\
	dw2_entries.c dw2_extra.c dw2_iface.c dw2_info.c dw2_lines.c\
	dw2_locdata.c dw2_types.c eval.c exp.c f64.c flags.c flpt.c flpt_fns.c\
	foralls.c getregs.c global_opt.c glopt.c guard.c inl_norm.c inline.c\
	inlinechoice.c inst_fmt.c install_fns.c installglob.c is_worth.c\
	label_ops.c labels.c li_fns.c locate.c machine.c machine_toks.c\
	makecode.c mark_scope.c me_fns.c misc_c.c move.c muldvrem.c needscan.c\
	oprators.c proc.c read_fns.c read_sort.c readglob.c regable.c\
	regalloc.c regexps.c sparcdiags.c sparcins.c sparctrans.c spec_tok.c\
	special.c table_fns.c tempdecs.c translat.c unroll.c weights.c xalloc.c

.PATH:	${SRC1} ${SRC2} ${SRC3} ${SRC4} ${SRC5} ${SRC6} ${SRC7}

#MAKE_TDF=make_tdf
#REMOVE=rm -f
#
#TDF_OUT=${SRC6}/decoder.c ${SRC6}/ecodes.h ${SRC6}/externs.h ${SRC6}/inits.h\
# ${SRC6}/main_reads.h ${SRC6}/temp_fns.new
#
#auto : ${TDF_OUT}
#
#${SRC6}/decoder.c : ${SPEC} ${SRC7}/decoder.c
#	@${REMOVE} ${SRC6}/decoder.c
#	${MAKE_TDF} ${SPEC} ${SRC7}/decoder.c ${SRC6}/decoder.c
#
#${SRC6}/ecodes.h : ${SPEC} ${SRC7}/ecodes.h
#	@${REMOVE} ${SRC6}/ecodes.h
#	${MAKE_TDF} ${SPEC} ${SRC7}/ecodes.h ${SRC6}/ecodes.h
#
#${SRC6}/externs.h : ${SPEC} ${SRC7}/externs.h
#	@${REMOVE} ${SRC6}/externs.h
#	${MAKE_TDF} ${SPEC} ${SRC7}/externs.h ${SRC6}/externs.h
#
#${SRC6}/inits.h : ${SPEC} ${SRC7}/inits.h
#	@${REMOVE} ${SRC6}/inits.h
#	${MAKE_TDF} ${SPEC} ${SRC7}/inits.h ${SRC6}/inits.h
#
#${SRC6}/main_reads.h : ${SPEC} ${SRC7}/main_reads.h
#	@${REMOVE} ${SRC6}/main_reads.h
#	${MAKE_TDF} ${SPEC} ${SRC7}/main_reads.h ${SRC6}/main_reads.h
#
#${SRC6}/temp_fns.new : ${SPEC} ${SRC7}/temp_fns.c
#	@${REMOVE} ${SRC6}/temp_fns.new
#	${MAKE_TDF} ${SPEC} ${SRC7}/temp_fns.c ${SRC6}/temp_fns.new
#
#auto_clobber :
#	${REMOVE} ${TDF_OUT}

.include "../Makefile.inc"
