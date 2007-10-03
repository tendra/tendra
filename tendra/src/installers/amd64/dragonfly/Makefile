# $Id$

# Standard directories and files
SRCC=${.CURDIR}/../../common
SRC1=${.CURDIR}/../common
SRC2=${SRCC}/construct
SRC3=${SRCC}/diag
SRC4=${SRCC}/linkinfo
SRC5=${SRCC}/reader
SRC6=${SRCC}/templ
SPEC=${BASE_DIR}/src/lib/tdf/def_4_1.db

# Standard variables

#TCCOPTS=-Xc -Y32bit -Yansi
CCOPTS=	-I${BASE_DIR}/${INCLUDE} -I${.CURDIR} -I${SRCC} -I${SRC1}\
	-I${SRC2} -I${SRC3} -I${SRC4} -I${SRC5} -I${SRC6}
LIBS=

# Dependencies and construction rules

PROG=	trans

SRCS=	aldefs.c assembler.c basicread.c c_arith_type.c case_opt.c check.c\
	check_id.c codec.c coder.c complex_eq.c const.c cproc.c decoder.c\
	dg_aux.c dg_fns.c diag_fns.c diag_info.c diag_out.c dw2_extra.c\
	evaluate.c exp.c f64.c flags.c flpt.c flpt_fns.c foralls.c\
	global_opt.c glopt.c inl_norm.c inline.c inlinechoice.c install_fns.c\
	installglob.c instr.c instr386.c is_worth.c label_ops.c li_fns.c\
	localflags.c machine.c machine_toks.c mark_scope.c me_fns.c misc_c.c\
	operand.c out.c overlap.c read_fns.c read_sort.c readglob.c\
	reg_record.c scan2.c spec.c spec_tok.c table_fns.c trans.c translate.c\
	tv_callees.c unroll.c weights.c xalloc.c

.PATH:	${SRC1} ${SRC2} ${SRC3} ${SRC4} ${SRC5} ${SRC6}


#MAKE_TDF=make_tdf
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
