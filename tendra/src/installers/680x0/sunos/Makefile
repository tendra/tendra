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

#TCCOPTS=	-Xc -Y32bit -Yposix
CCOPTS=	-I${BASE_DIR}/${INCLUDE} -I${.CURDIR} -I${SRCC} -I${SRC1}\
	-I${SRC2} -I${SRC3} -I${SRC4} -I${SRC5}
LIBS=

# Dependencies and construction rules

PROG=	trans

SRCS=	68k_globals.c aldefs.c case_opt.c check.c check_id.c codec.c coder.c\
	codex.c complex_eq.c const.c decoder.c dg_aux.c dg_fns.c diag_fns.c\
	diag_info.c evaluate.c exp.c f64.c flags.c flpt.c flpt_fns.c foralls.c\
	general_proc.c global_opt.c glopt.c inl_norm.c inline.c inliner.c\
	input.c install_fns.c installglob.c instr.c label_ops.c li_fns.c\
	mach_ins.c mach_op.c main.c mark_scope.c me_fns.c misc_c.c ops_float.c\
	ops_int.c ops_logic.c ops_misc.c output.c peephole.c read_fns.c\
	read_sort.c readglob.c scan2.c spec_tok.c special_exps.c stab_types.c\
	table_fns.c tests.c trans.c unroll.c utility.c weights.c where.c\
	xdb_basics.c xdb_output.c xdb_types.c

.PATH:	${SRC1} ${SRC2} ${SRC3} ${SRC4} ${SRC5} ${SRC6}

#MAKE_TDF=make_tdf
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
