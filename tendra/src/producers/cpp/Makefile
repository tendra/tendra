# $Id$

# Standard directories and files
SRC6=${.CURDIR}/syntax
SRC1=${.CURDIR}/../common
SRC2=${SRC1}/obj_c
SRC2A=${SRC1}/obj_tok
SRC2B=${SRC1}/obj_templ
SRC3=${SRC1}/construct
SRC4=${SRC1}/output
SRC5=${SRC1}/parse
SRC7=${SRC1}/utility
SPEC=${.CURDIR}/../../lib/tdf/def_4_1.db


#CAT=cat
#CALCULUS=calculus
#MAKE_ERR=make_err
#MAKE_TDF=make_tdf
#SID=sid
#SIDOPTS=-l ossg-c -s numeric -s split -s no-lines
#
#ALG=${SRC1}/c_class.alg
#TEMPL=${SRC2B}/bits.h ${SRC2B}/err_ext.h ${SRC2B}/loc_ext.h
#SYNTAX=${SRC6}/syntax.sid ${SRC6}/syntax.act
#PSYNTAX=${SRC5}/psyntax.sid ${SRC5}/psyntax.act
#
#SID_OUT=${SRC6}/syntax1.c ${SRC6}/syntax.h
#PSID_OUT=${SRC5}/psyntax1.c ${SRC5}/psyntax.h
#C_OUT=${SRC2}/c_class.h
#TOK_OUT=${SRC2A}/c_class.h
#ERR_OUT=${SRC7}/errors1.h ${SRC7}/errors2.h ${SRC7}/errors3.h ${SRC7}/opts.h
#TDF_OUT=${SRC4}/tdf1.h
#
#ALL_OUT=${SID_OUT} ${PSID_OUT} ${C_OUT} ${TOK_OUT} ${ERR_OUT} ${TDF_OUT}
#
#auto : ${ALL_OUT}
#
#${SRC6}/syntax1.c : ${SYNTAX}
#	${SID} ${SIDOPTS} ${SYNTAX} ${SRC6}/syntax@.c ${SRC6}/syntax.h
#
#${SRC5}/psyntax1.c : ${PSYNTAX}
#	${SID} ${SIDOPTS} ${PSYNTAX} ${SRC5}/psyntax@.c ${SRC5}/psyntax.h
#
#${SRC2}/c_class.h : ${ALG} ${TEMPL}
#	@${REMOVE} ${SRC2}/*.h
#	${CALCULUS} -a -x ${ALG} ${SRC2}
#	${CALCULUS} ${ALG} -T${SRC2B}/bits.h ${SRC2}/bits.h
#	${CALCULUS} ${ALG} -T${SRC2B}/err_ext.h ${SRC2}/err_ext.h
#	${CALCULUS} ${ALG} -T${SRC2B}/loc_ext.h ${SRC2}/loc_ext.h
#
#${SRC2A}/c_class.h : ${ALG} ${TEMPL}
#	@${REMOVE} ${SRC2A}/*.h
#	${CALCULUS} -a -x -t ${ALG} ${SRC2A}
#	${CALCULUS} -t ${ALG} -T${SRC2B}/bits.h ${SRC2A}/bits.h
#	${CALCULUS} -t ${ALG} -T${SRC2B}/err_ext.h ${SRC2A}/err_ext.h
#	${CALCULUS} -t ${ALG} -T${SRC2B}/loc_ext.h ${SRC2A}/loc_ext.h
#
#${SRC7}/errors1.h : ${SRC7}/catalog.err
#	@${REMOVE} ${SRC7}/errors1.h
#	${MAKE_ERR} ${SRC7}/catalog.err ${SRC7}/errors1.h
#
#${SRC7}/errors2.h : ${SRC7}/catalog.err ${SRC7}/extra.err
#	@${REMOVE} ${SRC7}/errors2.h
#	${CAT} ${SRC7}/catalog.err ${SRC7}/extra.err | ${MAKE_ERR} > ${SRC7}/errors2.h
#
#${SRC7}/errors3.h : ${SRC7}/catalog.err ${SRC7}/extra.err
#	@${REMOVE} ${SRC7}/errors3.h
#	${CAT} ${SRC7}/catalog.err ${SRC7}/extra.err | ${MAKE_ERR} -d > ${SRC7}/errors3.h
#
#${SRC7}/opts.h : ${SRC7}/catalog.err
#	@${REMOVE} ${SRC7}/opts.h
#	${MAKE_ERR} -u ${SRC7}/catalog.err ${SRC7}/opts.h
#
#${SRC4}/tdf1.h : ${SPEC} ${SRC2B}/tdf1.h
#	@${REMOVE} ${SRC4}/tdf1.h
#	${MAKE_TDF} ${SPEC} ${SRC2B}/tdf1.h ${SRC4}/tdf1.h
#
#auto_clobber :
#	@${REMOVE} ${SRC6}/syntax*.c ${SRC6}/syntax.h
#	@${REMOVE} ${SRC5}/psyntax*.c ${SRC5}/psyntax.h
#	@${REMOVE} ${SRC2}/*.h
#	@${REMOVE} ${SRC2A}/*.h
#	@${REMOVE} ${ERR_OUT}
#	@${REMOVE} ${TDF_OUT}

.include "Makefile.inc"

TCCOPTS=	-Yposix1 -Xs
CCOPTS=		-I${SRC1} -I${SRC2} -I${SRC3} -I${SRC4} -I${SRC5}\
		-I${SRC6} -I${SRC7}

SRCS+=  ../common/construct/access.c
SRCS+=  ../common/construct/allocate.c
SRCS+=  ../common/construct/assign.c
SRCS+=  ../common/construct/basetype.c
SRCS+=  ../common/construct/cast.c
SRCS+=  ../common/construct/check.c
SRCS+=  ../common/construct/chktype.c
SRCS+=  ../common/construct/class.c
SRCS+=  ../common/construct/construct.c
SRCS+=  ../common/construct/convert.c
SRCS+=  ../common/construct/copy.c
SRCS+=  ../common/construct/declare.c
SRCS+=  ../common/construct/derive.c
SRCS+=  ../common/construct/destroy.c
SRCS+=  ../common/construct/exception.c
SRCS+=  ../common/construct/expression.c
SRCS+=  ../common/construct/function.c
SRCS+=  ../common/construct/identifier.c
SRCS+=  ../common/construct/initialise.c
SRCS+=  ../common/construct/instance.c
SRCS+=  ../common/construct/inttype.c
SRCS+=  ../common/construct/label.c
SRCS+=  ../common/construct/member.c
SRCS+=  ../common/construct/merge.c
SRCS+=  ../common/construct/namespace.c
SRCS+=  ../common/construct/operator.c
SRCS+=  ../common/construct/overload.c
SRCS+=  ../common/construct/printf.c
SRCS+=  ../common/construct/quality.c
SRCS+=  ../common/construct/redeclare.c
SRCS+=  ../common/construct/rewrite.c
SRCS+=  ../common/construct/statement.c
SRCS+=  ../common/construct/template.c
SRCS+=  ../common/construct/tokdef.c
SRCS+=  ../common/construct/token.c
SRCS+=  ../common/construct/typeid.c
SRCS+=  ../common/construct/variable.c
SRCS+=  ../common/construct/virtual.c

SRCS+=  ../common/utility/buffer.c
SRCS+=  ../common/utility/catalog.c
SRCS+=  ../common/utility/debug.c
SRCS+=  ../common/utility/error.c
SRCS+=  ../common/utility/option.c
SRCS+=  ../common/utility/print.c
SRCS+=  ../common/utility/system.c
SRCS+=  ../common/utility/xalloc.c

SRCS+=  ../common/obj_c/c_class.c

SRCS+=  ../common/output/capsule.c
SRCS+=  ../common/output/compile.c
SRCS+=  ../common/output/decode.c
SRCS+=  ../common/output/diag.c
SRCS+=  ../common/output/diag2.c
SRCS+=  ../common/output/dump.c
SRCS+=  ../common/output/encode.c
SRCS+=  ../common/output/exp.c
SRCS+=  ../common/output/init.c
SRCS+=  ../common/output/load.c
SRCS+=  ../common/output/mangle.c
SRCS+=  ../common/output/save.c
SRCS+=  ../common/output/shape.c
SRCS+=  ../common/output/stmt.c
SRCS+=  ../common/output/struct.c
SRCS+=  ../common/output/throw.c
SRCS+=  ../common/output/tok.c
SRCS+=  ../common/output/unmangle.c

SRCS+=  ../common/parse/char.c
SRCS+=  ../common/parse/constant.c
SRCS+=  ../common/parse/file.c
SRCS+=  ../common/parse/hash.c
SRCS+=  ../common/parse/lex.c
SRCS+=  ../common/parse/literal.c
SRCS+=  ../common/parse/macro.c
SRCS+=  ../common/parse/parse.c
SRCS+=  ../common/parse/pragma.c
SRCS+=  ../common/parse/predict.c
SRCS+=  ../common/parse/preproc.c
SRCS+=  ../common/parse/psyntax1.c
SRCS+=  ../common/parse/psyntax2.c
SRCS+=  ../common/parse/psyntax3.c
SRCS+=  ../common/parse/table.c

SRCS+=  ../common/main.c

SRCS+=  syntax/syntax1.c
SRCS+=  syntax/syntax2.c
SRCS+=  syntax/syntax3.c
SRCS+=  syntax/syntax4.c
SRCS+=  syntax/syntax5.c
SRCS+=  syntax/syntax6.c
SRCS+=  syntax/syntax7.c

.include <tendra.obj.mk>


PROG=	tcpplus

.include <tendra.prog.mk>

