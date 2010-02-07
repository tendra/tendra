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

.include "Makefile.inc"


CCOPTS=	-I${BASE_DIR}/${INCLUDE} -I${.CURDIR} -I${SRCC} -I${SRC1}\
	-I${SRC2} -I${SRC3} -I${SRC4} -I${SRC5} -I${SRC6}

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

SRCS+=	../../common/linkinfo/li_fns.c

SRCS+=	../../common/reader/basicread.c
SRCS+=	../../common/reader/decoder.c
SRCS+=	../../common/reader/read_fns.c
SRCS+=	../../common/reader/read_sort.c
SRCS+=	../../common/reader/readglob.c
SRCS+=	../../common/reader/table_fns.c
SRCS+=	../../common/reader/xalloc.c

SRCS+=	../common/c_arith_type.c
SRCS+=	../common/codec.c
SRCS+=	../common/coder.c
SRCS+=	../common/cproc.c
SRCS+=	../common/dw2_extra.c
SRCS+=	../common/evaluate.c
SRCS+=	../common/glopt.c
SRCS+=	../common/inlinechoice.c
SRCS+=	../common/instr.c
SRCS+=	../common/instr386.c
SRCS+=	../common/is_worth.c
SRCS+=	../common/localflags.c
SRCS+=	../common/machine_toks.c
SRCS+=	../common/operand.c
SRCS+=	../common/out.c
SRCS+=	../common/overlap.c
SRCS+=	../common/reg_record.c
SRCS+=	../common/scan2.c
SRCS+=	../common/spec.c
SRCS+=	../common/spec_tok.c
SRCS+=	../common/trans.c
SRCS+=	../common/translate.c
SRCS+=	../common/tv_callees.c
SRCS+=	../common/weights.c

SRCS+=	assembler.c
SRCS+=	diag_out.c
SRCS+=	machine.c

.include <tendra.obj.mk>


PROG=	trans

.include <tendra.prog.mk>

