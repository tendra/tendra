# $TenDRA$
#
# Entries so we know where our build utilities are and various other nits we
# need during the build process.
#

LEXI=		${OBJ_PREFIX}/utilities/lexi/lexi
SID=		${OBJ_PREFIX}/utilities/sid/sid
CALCULUS=	${OBJ_PREFIX}/utilities/calculus/calculus
MAKE_ERR=	${OBJ_PREFIX}/utilities/make_err/make_err
MAKE_TDF=	${OBJ_PREFIX}/utilities/make_tdf/make_tdf
TLD=		${OBJ_PREFIX}/tools/tld/tld
DISP=		${OBJ_PREFIX}/tools/disp/disp
PL=		${OBJ_PREFIX}/tools/pl/pl
TCC=		${OBJ_PREFIX}/tools/tcc/tcc
TNC=		${OBJ_PREFIX}/tools/tnc/tnc
TSPEC=		${OBJ_PREFIX}/tools/tspec/tspec

def:
	@${BIN_ECHO} "lexi:     ${LEXI}"
	@${BIN_ECHO} "sid:      ${SID}"
	@${BIN_ECHO} "calculus: ${CALCULUS}"
	@${BIN_ECHO} "make_err: ${MAKE_ERR}"
	@${BIN_ECHO} "make_tdf: ${MAKE_TDF}"
	@${BIN_ECHO} "tld:      ${TLD}"
	@${BIN_ECHO} "disp:     ${DISP}"
	@${BIN_ECHO} "pl:       ${PL}"
	@${BIN_ECHO} "tcc:      ${TCC}"
	@${BIN_ECHO} "tnc:      ${TNC}"
	@${BIN_ECHO} "tspec:    ${TSPEC}"
	@${BIN_ECHO} DEFAULT_BUILD:	${DEFAULT_BUILD}
