# $TenDRA: Makefile 2151 2005-10-17 11:14:32Z stefanf $
#
# We re-write our suffixes and have the suffix rule in this file.
# since it's a special case (sh scripts) there was no point in placing
# this into tendra.sys.mk

.if !defined(SRC_DIR)
SRC_DIR=        ${.CURDIR:C/(.*)\/src.*/\1/}
.endif

.if exists (${SRC_DIR}/config.mk)
.include "${SRC_DIR}/config.mk"
.endif

.SUFFIXES:	.sh

# Tools
WRAPPERS=	disp.sh pl.sh tld.sh tnc.sh tspec.sh

# Utilities
WRAPPERS+=	calculus.sh lexi.sh sid.sh

# The rest
WRAPPERS+=	tdfc2.sh trans.sh

.if defined(WITH_ADA)
# Ada producer
WRAPPERS+=	tdfada.sh
.endif

DEPEND_SRC=	${WRAPPERS:R} tcc-special tchk-special

#${WRAPPERS}:

.sh:  
	${BIN_CAT} ${.CURDIR}/common.sh | \
	${BIN_SED} ${SED_OPTS} | \
	${BIN_SED} ${SED_OPTS_BIN} > \
	${.OBJDIR}/${.TARGET}


# The tcc and tchk scripts are special
tcc-special:
	${BIN_CAT} ${.CURDIR}/tcc.sh | \
	${BIN_SED} ${SED_OPTS} | \
	${BIN_SED} ${SED_OPTS_BIN} > \
	${.OBJDIR}/tcc
tchk-special:
	${BIN_CAT} ${.CURDIR}/tchk.sh | \
	${BIN_SED} ${SED_OPTS} | \
	${BIN_SED} ${SED_OPTS_BIN} > \
	${.OBJDIR}/tchk



SED_OPTS=	\
		-e "s|-TENDRA_BASEDIR-|${INSTALL_DIR}|g" \
		-e "s|-TENDRA_VERSION-|${VER_TENDRA}|g" \
		-e "s|-BIN_RUN-|${.TARGET}|g"

SED_OPTS_BIN=	\
		-e "s|-BIN_SH-|${BIN_SH}|g" \
		-e "s|-BIN_ECHO-|${BIN_ECHO}|g"


CLEANFILES=	${WRAPPERS:R} tcc.sh tchk.sh

.include "${.CURDIR}/../../mk/base/tendra.prog.mk"
