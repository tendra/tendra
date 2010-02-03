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

#TCCOPTS=-Xc -Y32bit -Yansi
CCOPTS=	-I${BASE_DIR}/${INCLUDE} -I${.CURDIR} -I${SRCC} -I${SRC1}\
	-I${SRC2} -I${SRC3} -I${SRC4} -I${SRC5}
LIBS=

# Dependencies and construction rules

SRCS=	aldefs.c alpha_ins.c alphadiags.c basicread.c bstack.c case_opt.c\
	check.c check_id.c code_here.c coder.c comp_eq_exp.c complex_eq.c\
	const.c cross.c decoder.c dg_aux.c dg_fns.c diag_fns.c diag_info.c\
	driver.c dump_distr.c eval.c exp.c extern_adds.c f64.c fail.c file.c\
	flags.c float.c flpt.c flpt_fns.c foralls.c frames.c getregs.c\
	global_opt.c glopt.c guard.c handle_sregs.c inl_norm.c inline.c\
	inlinechoice.c inst_fmt.c install_fns.c installglob.c is_worth.c\
	label_ops.c labels.c li_fns.c locate.c machine.c machine_toks.c\
	makesymtab.c mark_scope.c me_fns.c misc_c.c move.c oddtest.c\
	operators.c out_ba.c pseudo.c read_fns.c read_sort.c readglob.c\
	regable.c regalloc.c regexps.c scan.c spec.c spec_tok.c special.c\
	symbol.c symdiags.c syms.c table_fns.c tempdecs.c translate.c\
	type_to_aux.c unroll.c weights.c xalloc.c

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

.include "Makefile.inc"


PROG=	trans

.include <tendra.prog.mk>

