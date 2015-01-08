# $Id$

# Copyright 2010-2011, The TenDRA Project.
#
# See doc/copyright/ for the full copyright terms.


.if !defined(_TENDRA_WORK_MACHTOK_MK_)
_TENDRA_WORK_MACHTOK_MK_=1

.include <tendra.base.mk>
.include <tendra.functions.mk>
.include <tendra.compiler.mk>


.if !defined(MACHTOK_EXCEPT)
.BEGIN:
	@${ECHO} '$${MACHTOK_EXCEPT} must be set'
	@${EXIT} 1;
.endif

.if !defined(MACHTOK_MODEL)
.BEGIN:
	@${ECHO} '$${MACHTOK_MODEL} must be set'
	@${EXIT} 1;
.endif

.if !defined(MACHTOK_FLOAT)
.BEGIN:
	@${ECHO} '$${MACHTOK_FLOAT} must be set'
	@${EXIT} 1;
.endif

.if !defined(MACHTOK_INT)
.BEGIN:
	@${ECHO} '$${MACHTOK_INT} must be set'
	@${EXIT} 1;
.endif

.if !defined(MACHTOK_CHAR)
.BEGIN:
	@${ECHO} '$${MACHTOK_CHAR} must be set'
	@${EXIT} 1;
.endif

.if !defined(MACHTOK_BITF)
.BEGIN:
	@${ECHO} '$${MACHTOK_BITF} must be set'
	@${EXIT} 1;
.endif

.if !defined(MACHTOK_ALIGN)
.BEGIN:
	@${ECHO} '$${MACHTOK_ALIGN} must be set'
	@${EXIT} 1;
.endif

.if !defined(MACHTOK_STRUCT)
.BEGIN:
	@${ECHO} '$${MACHTOK_STRUCT} must be set'
	@${EXIT} 1;
.endif

.if !defined(MACHTOK_VAR)
.BEGIN:
	@${ECHO} '$${MACHTOK_VAR} must be set'
	@${EXIT} 1;
.endif

TOKENS_COMMON?=	machines/common/tokens
TOKENS_MODEL?=	model
TOKENS_EXCEPT?=	except
TOKENS_MAP?=	map
TOKENS_FLOAT?=	float
TOKENS_INT?=  	int
TOKENS_CHAR?=  	char
TOKENS_BITF?=  	bitfield
TOKENS_ALIGN?= 	align
TOKENS_STRUCT?=	struct
TOKENS_VAR?=   	var

MAP_LANG += c
MAP_LANG += f


${OBJ_SDIR}/c_toks.j: ${BASE_DIR}/${TOKENS_COMMON}/c_toks.tpl
	@${CONDCREATE} "${OBJ_SDIR}"
	${TPL} ${.ALLSRC} ${.TARGET}

${OBJ_SDIR}/pun.j: ${BASE_DIR}/${TOKENS_COMMON}/pun.tpl
	@${CONDCREATE} "${OBJ_SDIR}"
	@${ECHO} "==> Translating ${WRKDIR}/${.ALLSRC}"
	${TPL} ${.ALLSRC} ${.TARGET}

${OBJ_SDIR}/model_toks.j: ${BASE_DIR}/${TOKENS_MODEL}/${MACHTOK_MODEL}
	@${CONDCREATE} "${OBJ_SDIR}"
	@${ECHO} "==> Translating ${WRKDIR}/${.ALLSRC}"
	${TPL} ${.ALLSRC} ${.TARGET}

${OBJ_SDIR}/float_toks.j: ${BASE_DIR}/${TOKENS_FLOAT}/${MACHTOK_FLOAT}
	@${CONDCREATE} "${OBJ_SDIR}"
	@${ECHO} "==> Translating ${WRKDIR}/${.ALLSRC}"
	${TPL} -I${BASE_DIR}/${TOKENS_FLOAT} ${.ALLSRC} ${.TARGET}

${OBJ_SDIR}/int_toks.j: ${BASE_DIR}/${TOKENS_INT}/${MACHTOK_INT}
	@${CONDCREATE} "${OBJ_SDIR}"
	@${ECHO} "==> Translating ${WRKDIR}/${.ALLSRC}"
	${TPL} -I${BASE_DIR}/${TOKENS_INT} ${.ALLSRC} ${.TARGET}

${OBJ_SDIR}/char_toks.j: ${BASE_DIR}/${TOKENS_CHAR}/${MACHTOK_CHAR}
	@${CONDCREATE} "${OBJ_SDIR}"
	@${ECHO} "==> Translating ${WRKDIR}/${.ALLSRC}"
	${TPL} -I${BASE_DIR}/${TOKENS_CHAR} ${.ALLSRC} ${.TARGET}

${OBJ_SDIR}/bitfield_toks.j: ${BASE_DIR}/${TOKENS_BITF}/${MACHTOK_BITF}
	@${CONDCREATE} "${OBJ_SDIR}"
	@${ECHO} "==> Translating ${WRKDIR}/${.ALLSRC}"
	${TPL} -I${BASE_DIR}/${TOKENS_BITF} ${.ALLSRC} ${.TARGET}

${OBJ_SDIR}/align_toks.j: ${BASE_DIR}/${TOKENS_ALIGN}/${MACHTOK_ALIGN}
	@${CONDCREATE} "${OBJ_SDIR}"
	@${ECHO} "==> Translating ${WRKDIR}/${.ALLSRC}"
	${TPL} -I${BASE_DIR}/${TOKENS_ALIGN} ${.ALLSRC} ${.TARGET}

${OBJ_SDIR}/struct_toks.j: ${BASE_DIR}/${TOKENS_STRUCT}/${MACHTOK_STRUCT}
	@${CONDCREATE} "${OBJ_SDIR}"
	@${ECHO} "==> Translating ${WRKDIR}/${.ALLSRC}"
	${TPL} -I${BASE_DIR}/${TOKENS_STRUCT} ${.ALLSRC} ${.TARGET}

${OBJ_SDIR}/var_toks.j: ${BASE_DIR}/${TOKENS_VAR}${MACHTOKS_VAR}
	@${CONDCREATE} "${OBJ_SDIR}"
	@${ECHO} "==> Translating ${TOKENS_VAR}/${MACHTOKS_VAR}"
	${TPL} -I${BASE_DIR}/${TOKENS_VAR} ${.ALLSRC} ${.TARGET}

.for lang in ${MAP_LANG}
${OBJ_SDIR}/map_${lang}.j: ${BASE_DIR}/${TOKENS_MAP}/${lang}.tpl
	@${CONDCREATE} "${OBJ_SDIR}"
	@${ECHO} "==> Translating ${WRKDIR}/${.ALLSRC}"
	${TPL} ${.ALLSRC} ${.TARGET}
.endfor

#
# Rules proper
#

# C Producer LPI library
${OBJ_SDIR}/c.tl: ${OBJ_SDIR}/sys.j
	@${CONDCREATE} "${OBJ_SDIR}"
	@${ECHO} "==> Linking ${WRKDIR}/${.TARGET:T}"
	${TLD} -mc ${TLDOPTS} -o ${.TARGET} ${.ALLSRC}

${OBJ_SDIR}/sys.j: ${OBJ_SDIR}/sys_toks.j
	@${CONDCREATE} "${OBJ_SDIR}"
	@${ECHO} "==> Rewriting ${WRKDIR}/${.TARGET:T}"
	${TNC} -t -d -L'.~' ${.ALLSRC} ${.TARGET}

.for lang in ${MAP_LANG}
${OBJ_SDIR}/sys_toks.j: ${OBJ_SDIR}/map_${lang}.j
.endfor

${OBJ_SDIR}/sys_toks.j: ${OBJ_SDIR}/c_toks.j \
	${OBJ_SDIR}/pun.j \
	${OBJ_SDIR}/model_toks.j ${OBJ_SDIR}/float_toks.j ${OBJ_SDIR}/int_toks.j \
	${OBJ_SDIR}/char_toks.j ${OBJ_SDIR}/bitfield_toks.j ${OBJ_SDIR}/align_toks.j ${OBJ_SDIR}/struct_toks.j
	@${CONDCREATE} "${OBJ_SDIR}"
	@${ECHO} "==> Linking ${WRKDIR}/${.TARGET:T}"
	${TLD} -o ${.TARGET} ${.ALLSRC}


.for lang in ${MAP_LANG}
${OBJ_SDIR}/target_tok.tl: ${OBJ_SDIR}/map_${lang}.j
.endfor

# Target-dependent token library
${OBJ_SDIR}/target_tok.tl: ${OBJ_SDIR}/pun.j \
		${OBJ_SDIR}/except_toks.t ${OBJ_SDIR}/var_toks.t \
		${OBJ_SDIR}/model_toks.j ${OBJ_SDIR}/float_toks.j ${OBJ_SDIR}/int_toks.j \
		${OBJ_SDIR}/char_toks.j ${OBJ_SDIR}/bitfield_toks.j ${OBJ_SDIR}/align_toks.j ${OBJ_SDIR}/struct_toks.j
	@rm -f ${.TARGET}
	@${CONDCREATE} "${OBJ_SDIR}"
	@${ECHO} "==> Linking ${WRKDIR}/${.TARGET:T}"
	${TLD} -mc ${TLDOPTS} -o ${.TARGET} ${.ALLSRC}

${OBJ_SDIR}/except_toks.t: ${OBJ_SDIR}/except_toks.j \
		${BASE_DIR}/${TOKENS_COMMON}/except_toks
	@${CONDCREATE} "${OBJ_SDIR}"
	@${ECHO} "==> Linking ${WRKDIR}/${.TARGET:T}"
	${TCC} -o ${.TARGET} ${TCCENVOPTS} -Ft \
		-Y${BASE_DIR}/${TOKENS_COMMON}/except_toks ${OBJ_SDIR}/except_toks.j

${OBJ_SDIR}/var_toks.t: ${OBJ_SDIR}/var_toks.j \
		${BASE_DIR}/${TOKENS_COMMON}/var_toks
	@${CONDCREATE} "${OBJ_SDIR}"
	@${ECHO} "==> Translating ${WRKDIR}/${.TARGET}"
	${TCC} -o ${.TARGET} ${TCCENVOPTS} -Ft \
		-Y${BASE_DIR}/${TOKENS_COMMON}/var_toks ${OBJ_SDIR}/var_toks.j

${OBJ_SDIR}/except_toks.j: ${BASE_DIR}/${TOKENS_EXCEPT}/${MACHTOK_EXCEPT}
	@${CONDCREATE} "${OBJ_SDIR}"
	@${ECHO} "==> Translating ${WRKDIR}/${.ALLSRC}"
	${TPL} ${.ALLSRC} ${.TARGET}



#
# Internal targets (for use by libtsl)
#

${OBJ_DIR}/src/target_tok.tl: ${OBJ_SDIR}/target_tok.tl
	@${ECHO} "==> Symlinking for libtsl use"
	@${CONDCREATE} "${OBJ_DIR}/src"
	${LN} -s ${.ALLSRC} ${.TARGET}

${OBJ_DIR}/src/c.tl: ${OBJ_SDIR}/c.tl
	@${ECHO} "==> Symlinking for libtsl use"
	@${CONDCREATE} "${OBJ_DIR}/src"
	${LN} -s ${.ALLSRC} ${.TARGET}



#
# User-facing targets
#

all:: ${OBJ_SDIR}/c.tl ${OBJ_DIR}/src/c.tl ${OBJ_DIR}/src/target_tok.tl


clean::
	${RMFILE} ${OBJ_SDIR}/c.tl ${OBJ_DIR}/src/target_tok.tl
	${RMFILE} ${OBJ_SDIR}/pun.j
	${RMFILE} ${OBJ_SDIR}/dep_toks.j ${OBJ_SDIR}/c_toks.j
	${RMFILE} ${OBJ_SDIR}/model_toks.j ${OBJ_SDIR}/float_toks.j ${OBJ_SDIR}/int_toks.j
	${RMFILE} ${OBJ_SDIR}/char_toks.j ${OBJ_SDIR}/bitfield_toks.j ${OBJ_SDIR}/align_toks.j ${OBJ_SDIR}/struct_toks.j
	${RMFILE} ${OBJ_SDIR}/sys.j ${OBJ_SDIR}/sys_toks.j
	${RMFILE} ${OBJ_SDIR}/except_toks.j ${OBJ_SDIR}/except_toks.t
	${RMFILE} ${OBJ_SDIR}/var_toks.j ${OBJ_SDIR}/var_toks.t
.for lang in ${MAP_LANG}
	${RMFILE} ${OBJ_SDIR}/map_${lang}.j
.endfor


install:: ${OBJ_SDIR}/c.tl ${OBJ_DIR}/src/c.tl ${OBJ_DIR}/src/target_tok.tl
	@${ECHO} "==> Installing target-dependent C LPI"
	@${CONDCREATE} "${PREFIX_LPI}"
	${INSTALL} -m 644 ${OBJ_SDIR}/c.tl "${PREFIX_LPI}/c.tl"



.endif	# !defined(_TENDRA_WORK_MACHTOK_MK_)
