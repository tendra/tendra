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
	@echo "lexi:     ${LEXI}"
	@echo "sid:      ${SID}"
	@echo "calculus: ${CALCULUS}"
	@echo "make_err: ${MAKE_ERR}"
	@echo "make_tdf: ${MAKE_TDF}"
	@echo "tld:      ${TLD}"
	@echo "disp:     ${DISP}"
	@echo "pl:       ${PL}"
	@echo "tcc:      ${TCC}"
	@echo "tnc:      ${TNC}"
	@echo "tspec:    ${TSPEC}"
	@echo DEFAULT_BUILD:	${DEFAULT_BUILD}
