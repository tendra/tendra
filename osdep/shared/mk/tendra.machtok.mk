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

.if !defined(MACHTOK_STACK)
.BEGIN:
	@${ECHO} '$${MACHTOK_STACK} must be set'
	@${EXIT} 1;
.endif

.if !defined(MACHTOK_VA)
.BEGIN:
	@${ECHO} '$${MACHTOK_STACK} must be set'
	@${EXIT} 1;
.endif

.if !defined(MACHTOK_PUN)
.BEGIN:
	@${ECHO} '$${MACHTOK_PUN} must be set'
	@${EXIT} 1;
.endif

TOKENS_EXCEPT?=	abi/except
TOKENS_MODEL?=	abi/model
TOKENS_FLOAT?=	abi/float
TOKENS_CHAR?=  	abi/char
TOKENS_BITF?=  	abi/bitfield
TOKENS_ALIGN?= 	abi/align
TOKENS_STRUCT?=	abi/struct
TOKENS_STACK?= 	abi/stack
TOKENS_VA?=   	abi/va
TOKENS_INT?=  	abi/int
TOKENS_PUN?=   	abi/pun

ABI += except
ABI += model
ABI += float
ABI += char
ABI += bitfield
ABI += align
ABI += struct
ABI += stack
ABI += va
ABI += int

TDI += except
TDI += va

DEP += int

${OBJ_SDIR}/abi_except.j: ${BASE_DIR}/${TOKENS_EXCEPT}/${MACHTOK_EXCEPT}
	@${CONDCREATE} "${OBJ_SDIR}"
	@${ECHO} "==> Translating ${WRKDIR}/${.ALLSRC}"
	${TPL} ${.ALLSRC} ${.TARGET}

${OBJ_SDIR}/abi_model.j: ${BASE_DIR}/${TOKENS_MODEL}/${MACHTOK_MODEL}
	@${CONDCREATE} "${OBJ_SDIR}"
	@${ECHO} "==> Translating ${WRKDIR}/${.ALLSRC}"
	${TPL} ${.ALLSRC} ${.TARGET}

${OBJ_SDIR}/abi_float.j: ${BASE_DIR}/${TOKENS_FLOAT}/${MACHTOK_FLOAT}
	@${CONDCREATE} "${OBJ_SDIR}"
	@${ECHO} "==> Translating ${WRKDIR}/${.ALLSRC}"
	${TPL} -I${BASE_DIR}/${TOKENS_FLOAT} ${.ALLSRC} ${.TARGET}

${OBJ_SDIR}/abi_char.j: ${BASE_DIR}/${TOKENS_CHAR}/${MACHTOK_CHAR}
	@${CONDCREATE} "${OBJ_SDIR}"
	@${ECHO} "==> Translating ${WRKDIR}/${.ALLSRC}"
	${TPL} -I${BASE_DIR}/${TOKENS_CHAR} ${.ALLSRC} ${.TARGET}

${OBJ_SDIR}/abi_bitfield.j: ${BASE_DIR}/${TOKENS_BITF}/${MACHTOK_BITF}
	@${CONDCREATE} "${OBJ_SDIR}"
	@${ECHO} "==> Translating ${WRKDIR}/${.ALLSRC}"
	${TPL} -I${BASE_DIR}/${TOKENS_BITF} ${.ALLSRC} ${.TARGET}

${OBJ_SDIR}/abi_align.j: ${BASE_DIR}/${TOKENS_ALIGN}/${MACHTOK_ALIGN}
	@${CONDCREATE} "${OBJ_SDIR}"
	@${ECHO} "==> Translating ${WRKDIR}/${.ALLSRC}"
	${TPL} -I${BASE_DIR}/${TOKENS_ALIGN} ${.ALLSRC} ${.TARGET}

${OBJ_SDIR}/abi_struct.j: ${BASE_DIR}/${TOKENS_STRUCT}/${MACHTOK_STRUCT}
	@${CONDCREATE} "${OBJ_SDIR}"
	@${ECHO} "==> Translating ${WRKDIR}/${.ALLSRC}"
	${TPL} -I${BASE_DIR}/${TOKENS_STRUCT} ${.ALLSRC} ${.TARGET}

${OBJ_SDIR}/abi_stack.j: ${BASE_DIR}/${TOKENS_STACK}${MACHTOKS_STACK}
	@${CONDCREATE} "${OBJ_SDIR}"
	@${ECHO} "==> Translating ${WRKDIR}/${.ALLSRC}"
	${TPL} -I${BASE_DIR}/${TOKENS_STACK} ${.ALLSRC} ${.TARGET}

${OBJ_SDIR}/abi_va.j: ${BASE_DIR}/${TOKENS_VA}${MACHTOKS_VA}
	@${CONDCREATE} "${OBJ_SDIR}"
	@${ECHO} "==> Translating ${WRKDIR}/${.ALLSRC}"
	${TPL} -I${BASE_DIR}/${TOKENS_VA} ${.ALLSRC} ${.TARGET}

${OBJ_SDIR}/abi_int.j: ${BASE_DIR}/${TOKENS_INT}${MACHTOKS_INT}
	@${CONDCREATE} "${OBJ_SDIR}"
	@${ECHO} "==> Translating ${WRKDIR}/${.ALLSRC}"
	${TPL} -I${BASE_DIR}/${TOKENS_VA} ${.ALLSRC} ${.TARGET}

${OBJ_SDIR}/abi_pun.j: ${BASE_DIR}/${TOKENS_PUN}/${MACHTOK_PUN}
	@${CONDCREATE} "${OBJ_SDIR}"
	@${ECHO} "==> Translating ${WRKDIR}/${.ALLSRC}"
	${TPL} ${.ALLSRC} ${.TARGET}

.for tdi in ${TDI}
${OBJ_SDIR}/tdi_${tdi}.j: ${BASE_DIR}/tdi/${tdi}.tpl
	@${CONDCREATE} "${OBJ_SDIR}"
	@${ECHO} "==> Translating ${WRKDIR}/${.ALLSRC}"
	${TPL} ${.ALLSRC} ${.TARGET}
.endfor

.for dep in ${DEP}
${OBJ_SDIR}/dep_${dep}.j: ${BASE_DIR}/dep/${dep}.tpl
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

.for abi in ${ABI}
${OBJ_SDIR}/abi.j: ${OBJ_SDIR}/abi_${abi}.j
.endfor

.for tdi in ${TDI}
${OBJ_SDIR}/tdi.j: ${OBJ_SDIR}/tdi_${tdi}.j
.endfor

.for dep in ${DEP}
${OBJ_SDIR}/dep.j: ${OBJ_SDIR}/dep_${dep}.j
.endfor

${OBJ_SDIR}/abi.j:
	@${CONDCREATE} "${OBJ_SDIR}"
	@${ECHO} "==> Linking ${WRKDIR}/${.TARGET:T}"
	${TLD} -o ${.TARGET} ${.ALLSRC}

${OBJ_SDIR}/tdi.j:
	@${CONDCREATE} "${OBJ_SDIR}"
	@${ECHO} "==> Linking ${WRKDIR}/${.TARGET:T}"
	${TLD} -o ${.TARGET} ${.ALLSRC}

${OBJ_SDIR}/dep.j:
	@${CONDCREATE} "${OBJ_SDIR}"
	@${ECHO} "==> Linking ${WRKDIR}/${.TARGET:T}"
	${TLD} -o ${.TARGET} ${.ALLSRC}

${OBJ_SDIR}/sys_toks.j: ${OBJ_SDIR}/tdi.j ${OBJ_SDIR}/dep.j ${OBJ_SDIR}/abi.j
	@${CONDCREATE} "${OBJ_SDIR}"
	@${ECHO} "==> Linking ${WRKDIR}/${.TARGET:T}"
	${TLD} -o ${.TARGET} ${.ALLSRC}



#
# Internal targets (for use by libtsl)
#

${OBJ_DIR}/src/c.tl: ${OBJ_SDIR}/c.tl
	@${ECHO} "==> Symlinking for libtsl use"
	@${CONDCREATE} "${OBJ_DIR}/src"
	${LN} -s ${.ALLSRC} ${.TARGET}

${OBJ_DIR}/src/sys_toks.j: ${OBJ_SDIR}/sys_toks.j
	@${ECHO} "==> Symlinking for libtsl use"
	@${CONDCREATE} "${OBJ_DIR}/src"
	${LN} -s ${.ALLSRC} ${.TARGET}



#
# User-facing targets
#

all:: ${OBJ_SDIR}/c.tl ${OBJ_DIR}/src/c.tl


clean::
	${RMFILE} ${OBJ_SDIR}/c.tl
	${RMFILE} ${OBJ_SDIR}/tdi.j
	${RMFILE} ${OBJ_SDIR}/dep.j
	${RMFILE} ${OBJ_SDIR}/abi.j
	${RMFILE} ${OBJ_SDIR}/dep_toks.j
	${RMFILE} ${OBJ_SDIR}/sys.j ${OBJ_SDIR}/sys_toks.j
.for abi in ${ABI}
	${RMFILE} ${OBJ_SDIR}/abi_${abi}.j
.endfor
.for dep in ${DEP}
	${RMFILE} ${OBJ_SDIR}/dep_${dep}.j
.endfor


install:: ${OBJ_SDIR}/c.tl ${OBJ_DIR}/src/c.tl ${OBJ_DIR}/src/sys_toks.j
	@${ECHO} "==> Installing target-dependent C LPI"
	@${CONDCREATE} "${PREFIX_LPI}"
	${INSTALL} -m 644 ${OBJ_SDIR}/c.tl "${PREFIX_LPI}/c.tl"



.endif	# !defined(_TENDRA_WORK_MACHTOK_MK_)
