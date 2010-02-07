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

.include "Makefile.inc"


#TCCOPTS=	-Xc -Y32bit -Yposix
CCOPTS=	-I${BASE_DIR}/${INCLUDE} -I${.CURDIR} -I${SRCC} -I${SRC1}\
	-I${SRC2} -I${SRC3} -I${SRC4} -I${SRC5}

SRCS+=	../../common/construct/aldefs.c
SRCS+=	../../common/construct/case_opt.c
SRCS+=	../../common/construct/check.c
SRCS+=	../../common/construct/check_id.c
SRCS+=	../../common/construct/complex_eq.c
SRCS+=	../../common/construct/const.c
SRCS+=	../../common/construct/exp.c
SRCS+=	../../common/construct/f64.c
SRCS+=	../../common/construct/flags.c
SRCS+=	../../common/construct/flpt.c
SRCS+=	../../common/construct/flpt_fns.c
SRCS+=	../../common/construct/foralls.c
SRCS+=	../../common/construct/global_opt.c
SRCS+=	../../common/construct/inl_norm.c
SRCS+=	../../common/construct/inline.c
SRCS+=	../../common/construct/install_fns.c
SRCS+=	../../common/construct/installglob.c
SRCS+=	../../common/construct/label_ops.c
SRCS+=	../../common/construct/me_fns.c
SRCS+=	../../common/construct/misc_c.c
SRCS+=	../../common/construct/unroll.c

SRCS+=	../../common/diag/dg_aux.c
SRCS+=	../../common/diag/dg_fns.c
SRCS+=	../../common/diag/diag_fns.c
SRCS+=	../../common/diag/diag_info.c
SRCS+=	../../common/diag/mark_scope.c

#SRCS+=	../../common/reader/basicread.c
SRCS+=	../../common/reader/decoder.c
SRCS+=	../../common/reader/read_fns.c
SRCS+=	../../common/reader/read_sort.c
SRCS+=	../../common/reader/readglob.c
SRCS+=	../../common/reader/table_fns.c
#SRCS+=	../../common/reader/xalloc.c

SRCS+=	../common/68k_globals.c
SRCS+=	../common/codec.c
SRCS+=	../common/coder.c
SRCS+=	../common/codex.c
SRCS+=	../common/evaluate.c
SRCS+=	../common/general_proc.c
SRCS+=	../common/glopt.c
SRCS+=	../common/inliner.c
SRCS+=	../common/input.c
SRCS+=	../common/instr.c
SRCS+=	../common/mach_ins.c
SRCS+=	../common/mach_op.c
SRCS+=	../common/ops_float.c
SRCS+=	../common/ops_int.c
SRCS+=	../common/ops_logic.c
SRCS+=	../common/ops_misc.c
SRCS+=	../common/output.c
SRCS+=	../common/peephole.c
SRCS+=	../common/scan2.c
SRCS+=	../common/spec_tok.c
SRCS+=	../common/special_exps.c
SRCS+=	../common/stab_types.c
SRCS+=	../common/tests.c
SRCS+=	../common/trans.c
SRCS+=	../common/utility.c
SRCS+=	../common/weights.c
SRCS+=	../common/where.c
SRCS+=	../common/xdb_basics.c
SRCS+=	../common/xdb_output.c
SRCS+=	../common/xdb_types.c

SRCS+=	main.c

.include <tendra.obj.mk>


PROG=	trans

.include <tendra.prog.mk>

