# TenDRA make build infrastructure
#
# $Id$

.if !defined(_TENDRA_WORK_MACHTOK_MK_)
_TENDRA_WORK_MACHTOK_MK_=1

.include <tendra.base.mk>

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



#
# External dependencies
#

${OBJ_DIR}/${TOKENS_COMMON}/var_toks.t:
	@cd ${BASE_DIR}/${TOKENS_COMMON} && ${MAKE} ${.TARGET}

${OBJ_DIR}/${TOKENS_COMMON}/c_toks.j:
	@cd ${BASE_DIR}/${TOKENS_COMMON} && ${MAKE} ${.TARGET}



#
# Rules proper
#

${OBJ_SDIR}:
	${MKDIR} -p ${.TARGET}

.for src in ${MACHTOK_EXCEPT} ${MACHTOK_VAR}
${OBJ_SDIR}/${src:R}.t: ${OBJ_SDIR} ${OBJ_SDIR}/${src:R}.j \
	${BASE_DIR}/${TOKENS_COMMON}/${src:R}
	@${ECHO} "==> Linking ${WRKDIR}/${.TARGET:T}"
	${TCC} ${TCCOPTS} -Y${BASE_DIR}/${TOKENS_COMMON}/${src:R} \
	    -Ft -o ${.TARGET} ${OBJ_SDIR}/${src:R}.j
.endfor

.for src in ${MACHTOK_DEP} ${MACHTOK_MAP} ${MACHTOK_VAR} ${MACHTOK_EXCEPT}
${OBJ_SDIR}/${src:S/.tpl/.j/}: ${OBJ_SDIR} ${src}
	@${ECHO} "==> Translating ${WRKDIR}/${src}"
	${TPL} ${TPLOPTS} ${src} ${.TARGET}
.endfor

_machtok_target+=	${OBJ_SDIR}/${MACHTOK_DEP:R}.j
_machtok_target+=	${OBJ_SDIR}/${MACHTOK_MAP:R}.j
_machtok_target+=	${OBJ_SDIR}/${MACHTOK_EXCEPT:R}.t
.if "${MACHTOK_VAR}" != ""
_machtok_target+=	${OBJ_SDIR}/${MACHTOK_VAR:R}.t
.else
_machtok_target+=	${OBJ_SDIR}/${TOKENS_COMMON}/var_toks.t
.endif

# depended on as ${TDFLIB} by tendra.tokdef.mk
${OBJ_SDIR}/target_tok.tl: ${OBJ_SDIR} ${_machtok_target}
	@${ECHO} "==> Linking ${WRKDIR}/${.TARGET:T}"
	${TLD} ${TLDOPTS} -o ${.TARGET} ${_machtok_target}

# depended on by tendra.api.mk
${OBJ_SDIR}/sys.j: ${OBJ_SDIR} ${OBJ_SDIR}/sys_toks.j
	@${ECHO} "==> Rewriting ${WRKDIR}/${.TARGET:T}"
	${TNC} -o ${.TARGET} -t -d -L'.~' ${.ALLSRC:M*.j}

${OBJ_SDIR}/sys_toks.j: ${OBJ_SDIR} ${OBJ_DIR}/${TOKENS_COMMON}/c_toks.j \
	${OBJ_SDIR}/dep_toks.j ${OBJ_SDIR}/map_toks.j
	@${ECHO} "==> Linking ${WRKDIR}/${.TARGET:T}"
	${TLD} -o ${.TARGET} ${.ALLSRC:M*.j}



#
# User-facing targets
#

all::


clean::
	${REMOVE} ${OBJ_SDIR}/${MACHTOK_DEP:R}.j
	${REMOVE} ${OBJ_SDIR}/${MACHTOK_MAP:R}.j
	${REMOVE} ${OBJ_SDIR}/${MACHTOK_EXCEPT:R}.j ${OBJ_SDIR}/${MACHTOK_EXCEPT:R}.t
.if "${MACHTOK_VAR}" != ""
	${REMOVE} ${OBJ_SDIR}/${MACHTOK_VAR:R}.j ${OBJ_SDIR}/${MACHTOK_VAR:R}.t
.endif
	${REMOVE} ${OBJ_SDIR}/except_toks.j ${OBJ_SDIR}/sys_toks.j ${OBJ_SDIR}/sys.j
	@cd ${BASE_DIR}/${TOKENS_COMMON} && ${MAKE} clean


install::



.endif	# !defined(_TENDRA_WORK_MACHTOK_MK_)
