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

.if !defined(MACHTOK_BITFIELD)
.BEGIN:
	@${ECHO} '$${MACHTOK_BITFIELD} must be set'
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

.for abi in ${ABI}
${OBJ_SDIR}/abi_${abi}.j: ${BASE_DIR}/abi/${abi}/${MACHTOK_${abi:tu}}
	@${CONDCREATE} "${OBJ_SDIR}"
	@${ECHO} "==> Translating ${abi}/${MACHTOK_${abi:tu}}"
	${TPL} -I${BASE_DIR}/abi/${abi} ${.ALLSRC} ${.TARGET}
.endfor

.for abi in ${ABI}
${OBJ_SDIR}/abi.tl: ${OBJ_SDIR}/abi_${abi}.j
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
	${RMFILE} ${OBJ_SDIR}/abi_${abi}.j
.endfor


install:: ${OBJ_SDIR}/abi.tl
	@${ECHO} "==> Installing target-dependent C LPI"
	@${CONDCREATE} "${PREFIX_LPI}"
	${INSTALL} -m 644 ${OBJ_SDIR}/abi.tl "${PREFIX_SYS}/abi.tl"



.endif	# !defined(_TENDRA_WORK_MACHTOK_MK_)
