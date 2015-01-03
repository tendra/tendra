# $Id$

# Copyright 2010-2011, The TenDRA Project.
#
# See doc/copyright/ for the full copyright terms.


.if !defined(_TENDRA_WORK_MACHTOK_MK_)
_TENDRA_WORK_MACHTOK_MK_=1

.include <tendra.base.mk>
.include <tendra.functions.mk>
.include <tendra.compiler.mk>


.if !defined(MACHTOK_DEP)
.BEGIN:
	@${ECHO} '$${MACHTOK_DEP} must be set'
	@${EXIT} 1;
.endif

.if !defined(MACHTOK_MAP)
.BEGIN:
	@${ECHO} '$${MACHTOK_MAP} must be set'
	@${EXIT} 1;
.endif

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

TOKENS_COMMON?=	machines/common/tokens
TOKENS_MODEL?=	model

.if !defined(MACHTOK_VAR)
_machtok_target+=	${OBJ_SDIR}/${TOKENS_COMMON}/var_toks.t
.endif


${OBJ_SDIR}/c_toks.j: ${BASE_DIR}/${TOKENS_COMMON}/c_toks.tpl
	@${CONDCREATE} "${OBJ_SDIR}"
	${TPL} ${.ALLSRC} ${.TARGET}

${OBJ_SDIR}/dep_toks.j: ${MACHTOK_DEP}
	@${CONDCREATE} "${OBJ_SDIR}"
	@${ECHO} "==> Translating ${WRKDIR}/${.ALLSRC}"
	${TPL} ${.ALLSRC} ${.TARGET}

${OBJ_SDIR}/model_toks.j: ${BASE_DIR}/${TOKENS_MODEL}/${MACHTOK_MODEL}
	@${CONDCREATE} "${OBJ_SDIR}"
	@${ECHO} "==> Translating ${WRKDIR}/${.ALLSRC}"
	${TPL} ${.ALLSRC} ${.TARGET}



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

${OBJ_SDIR}/sys_toks.j: ${OBJ_SDIR}/c_toks.j ${OBJ_SDIR}/dep_toks.j \
	${OBJ_SDIR}/map_toks.j ${OBJ_SDIR}/model_toks.j
	@${CONDCREATE} "${OBJ_SDIR}"
	@${ECHO} "==> Linking ${WRKDIR}/${.TARGET:T}"
	${TLD} -o ${.TARGET} ${.ALLSRC}



# Target-dependent token library
${OBJ_SDIR}/target_tok.tl: ${OBJ_SDIR}/dep_toks.j ${OBJ_SDIR}/map_toks.j \
		${OBJ_SDIR}/except_toks.t ${OBJ_SDIR}/var_toks.t ${OBJ_SDIR}/model_toks.j
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

.if defined(MACHTOK_VAR)
${OBJ_SDIR}/var_toks.j: ${MACHTOK_VAR}
.else
${OBJ_SDIR}/var_toks.j: ${BASE_DIR}/${TOKENS_COMMON}/var_toks.tpl
.endif
	@${CONDCREATE} "${OBJ_SDIR}"
.if defined(MACHTOK_VAR)
	@${ECHO} "==> Translating ${WRKDIR}/${.ALLSRC}"
.else
	@${ECHO} "==> Translating ${TOKENS_COMMON}/var_toks.tpl"
.endif
	${TPL} ${.ALLSRC} ${.TARGET}

${OBJ_SDIR}/map_toks.j: ${MACHTOK_MAP}
	@${CONDCREATE} "${OBJ_SDIR}"
	@${ECHO} "==> Translating ${WRKDIR}/${.ALLSRC}"
	${TPL} ${.ALLSRC} ${.TARGET}

${OBJ_SDIR}/except_toks.j: ${MACHTOK_EXCEPT}
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
	${RMFILE} ${OBJ_SDIR}/dep_toks.j ${OBJ_SDIR}/c_toks.j ${OBJ_SDIR}/map_toks.j
	${RMFILE} ${OBJ_SDIR}/sys.j ${OBJ_SDIR}/sys_toks.j
	${RMFILE} ${OBJ_SDIR}/except_toks.j ${OBJ_SDIR}/except_toks.t
	${RMFILE} ${OBJ_SDIR}/var_toks.j ${OBJ_SDIR}/var_toks.t


install:: ${OBJ_SDIR}/c.tl ${OBJ_DIR}/src/c.tl ${OBJ_DIR}/src/target_tok.tl
	@${ECHO} "==> Installing target-dependent C LPI"
	@${CONDCREATE} "${PREFIX_LPI}"
	${INSTALL} -m 644 ${OBJ_SDIR}/c.tl "${PREFIX_LPI}/c.tl"



.endif	# !defined(_TENDRA_WORK_MACHTOK_MK_)
