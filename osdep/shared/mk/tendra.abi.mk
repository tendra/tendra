# $Id$

# Copyright 2010-2011, The TenDRA Project.
#
# See doc/copyright/ for the full copyright terms.


.if !defined(_TENDRA_WORK_ABI_MK_)
_TENDRA_WORK_ABI_MK_=1

.include <tendra.base.mk>
.include <tendra.functions.mk>
.include <tendra.compiler.mk>


.if !defined(ABI_EXCEPT)
.BEGIN:
	@${ECHO} '$${ABI_EXCEPT} must be set'
	@${EXIT} 1;
.endif

.if !defined(ABI_MODEL)
.BEGIN:
	@${ECHO} '$${ABI_MODEL} must be set'
	@${EXIT} 1;
.endif

.if !defined(ABI_FLOAT)
.BEGIN:
	@${ECHO} '$${ABI_FLOAT} must be set'
	@${EXIT} 1;
.endif

.if !defined(ABI_INT)
.BEGIN:
	@${ECHO} '$${ABI_INT} must be set'
	@${EXIT} 1;
.endif

.if !defined(ABI_CHAR)
.BEGIN:
	@${ECHO} '$${ABI_CHAR} must be set'
	@${EXIT} 1;
.endif

.if !defined(ABI_BITFIELD)
.BEGIN:
	@${ECHO} '$${ABI_BITFIELD} must be set'
	@${EXIT} 1;
.endif

.if !defined(ABI_ALIGN)
.BEGIN:
	@${ECHO} '$${ABI_ALIGN} must be set'
	@${EXIT} 1;
.endif

.if !defined(ABI_STRUCT)
.BEGIN:
	@${ECHO} '$${ABI_STRUCT} must be set'
	@${EXIT} 1;
.endif

.if !defined(ABI_STACK)
.BEGIN:
	@${ECHO} '$${ABI_STACK} must be set'
	@${EXIT} 1;
.endif

.if !defined(ABI_VA)
.BEGIN:
	@${ECHO} '$${ABI_STACK} must be set'
	@${EXIT} 1;
.endif

.if !defined(ABI_PUN)
.BEGIN:
	@${ECHO} '$${ABI_PUN} must be set'
	@${EXIT} 1;
.endif


ABI += except
ABI += model
ABI += float
ABI += int
ABI += char
ABI += bitfield
ABI += align
ABI += struct
ABI += pun
ABI += stack
ABI += va


#
# Rules proper
#

# openbsd make(1) doesn't have :tu
.for abi in ${ABI}
TU_${abi} != ${ECHO} ${abi} | ${TR} a-z A-Z
.endfor

.for abi in ${ABI}
${OBJ_SDIR}/${abi}.j: ${BASE_DIR}/abi/${abi}/${ABI_${TU_${abi}}}
	@${CONDCREATE} "${OBJ_SDIR}"
	@${ECHO} "==> Translating ${abi}/${ABI_${TU_${abi}}}"
	${TPL} -I${BASE_DIR}/abi/${abi} ${.ALLSRC} ${.TARGET}
.endfor

.for abi in ${ABI}
${OBJ_SDIR}/abi.tl: ${OBJ_SDIR}/${abi}.j
.endfor

${OBJ_SDIR}/abi.tl:
	@${CONDCREATE} "${OBJ_SDIR}"
	@${ECHO} "==> Linking ${WRKDIR}/${.TARGET:T}"
	${TLD} -mc ${TLDOPTS} -o ${.TARGET} ${.ALLSRC}

#${OBJ_SDIR}/sys.j: ${OBJ_SDIR}/sys_toks.j
#	@${CONDCREATE} "${OBJ_SDIR}"
#	@${ECHO} "==> Rewriting ${WRKDIR}/${.TARGET:T}"
#	${TNC} -t -d -L'.~' ${.ALLSRC} ${.TARGET}

${OBJ_SDIR}/abi.tl:
	@${CONDCREATE} "${OBJ_SDIR}"
	@${ECHO} "==> Linking ${WRKDIR}/${.TARGET:T}"
	${TLD} -o ${.TARGET} ${.ALLSRC}



#
# User-facing targets
#

all:: ${OBJ_SDIR}/abi.tl


clean::
.for abi in ${ABI}
	${RMFILE} ${OBJ_SDIR}/${abi}.j
.endfor


install:: ${OBJ_SDIR}/abi.tl
	@${ECHO} "==> Installing target-dependent C LPI"
	@${CONDCREATE} "${PREFIX_LPI}"
	${INSTALL} -m 644 ${OBJ_SDIR}/abi.tl "${PREFIX_SYS}/abi.tl"



.endif	# !defined(_TENDRA_WORK_ABI_MK_)
