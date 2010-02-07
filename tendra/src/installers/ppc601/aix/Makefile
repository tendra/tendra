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


#TCCOPTS=-Xc -Y32bit -Yansi
CCOPTS=	-I${BASE_DIR}/${INCLUDE} -I${.CURDIR} -I${SRCC} -I${SRC1}\
	-I${SRC2} -I${SRC3} -I${SRC4} -I${SRC5} -I../../power/aix -I../../power/common

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

SRCS+=	../../power/common/ash.c
SRCS+=	../../power/common/codehere.c
SRCS+=	../../power/common/comment.c
SRCS+=	../../power/common/diagout.c
SRCS+=	../../power/common/dynamic_init.c
SRCS+=	../../power/common/error.c
SRCS+=	../../power/common/eval.c
SRCS+=	../../power/common/frames.c
SRCS+=	../../power/common/getregs.c
SRCS+=	../../power/common/glopt.c
SRCS+=	../../power/common/guard.c
SRCS+=	../../power/common/inlinechoice.c
SRCS+=	../../power/common/inst_fmt.c
SRCS+=	../../power/common/instruct.c
SRCS+=	../../power/common/is_worth.c
SRCS+=	../../power/common/labels.c
SRCS+=	../../power/common/locate.c
SRCS+=	../../power/common/machine.c
SRCS+=	../../power/common/machine_toks.c
SRCS+=	../../power/common/macro.c
SRCS+=	../../power/common/makecode.c
SRCS+=	../../power/common/mask.c
SRCS+=	../../power/common/mem_copy.c
SRCS+=	../../power/common/move.c
SRCS+=	../../power/common/muldvrem.c
SRCS+=	../../power/common/needscan.c
SRCS+=	../../power/common/oprators.c
SRCS+=	../../power/common/parameter.c
SRCS+=	../../power/common/pp.c
SRCS+=	../../power/common/proc.c
SRCS+=	../../power/common/record_bit.c
SRCS+=	../../power/common/regable.c
SRCS+=	../../power/common/regalloc.c
SRCS+=	../../power/common/regexps.c
SRCS+=	../../power/common/spec.c
SRCS+=	../../power/common/spec_tok.c
SRCS+=	../../power/common/stack.c
SRCS+=	../../power/common/tempdecs.c
SRCS+=	../../power/common/translat.c
SRCS+=	../../power/common/weights.c

SRCS+=	../../power/powertrans.c

.include <tendra.obj.mk>


PROG=	trans

.include <tendra.prog.mk>

