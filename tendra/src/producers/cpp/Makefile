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

# Standard variables

TCCOPTS=	-Yposix1 -Xs
CCOPTS=		-I${SRC1} -I${SRC2} -I${SRC3} -I${SRC4} -I${SRC5}\
		-I${SRC6} -I${SRC7}
LIBS=

# Dependencies and construction rules

PROG=	tcpplus

SRCS=	access.c allocate.c assign.c basetype.c buffer.c c_class.c capsule.c\
	cast.c catalog.c char.c check.c chktype.c class.c compile.c constant.c\
	construct.c convert.c copy.c debug.c declare.c decode.c derive.c\
	destroy.c diag.c diag2.c dump.c encode.c error.c exception.c exp.c\
	expression.c file.c function.c hash.c identifier.c init.c initialise.c\
	instance.c inttype.c label.c lex.c literal.c load.c macro.c main.c\
	mangle.c member.c merge.c namespace.c operator.c option.c overload.c\
	parse.c pragma.c predict.c preproc.c print.c printf.c psyntax1.c\
	psyntax2.c psyntax3.c quality.c redeclare.c rewrite.c save.c shape.c\
	statement.c stmt.c struct.c syntax1.c syntax2.c syntax3.c syntax4.c\
	syntax5.c syntax6.c syntax7.c system.c table.c template.c throw.c\
	tok.c tokdef.c token.c typeid.c unmangle.c variable.c virtual.c\
	xalloc.c

.PATH:	${SRC1} ${SRC2} ${SRC3} ${SRC4} ${SRC5} ${SRC6} ${SRC7}

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
