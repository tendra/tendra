# $TenDRA$
#
# We re-write our suffixes and have the suffix rule in this file.
# since it's a special case (sh scripts) there was no point in placing
# this into tendra.sys.mk

.SUFFIXES:	.sh

# Tools
WRAPPERS=	disp.sh pl.sh tld.sh tnc.sh tspec.sh

# Utilities
WRAPPERS+=	calculus.sh lexi.sh sid.sh tchk.sh

# The rest
WRAPPERS+=	tdfc2.sh trans.sh

DEPEND_SRC=	${WRAPPERS:R} tcc-special

#${WRAPPERS}:

.sh:  
	${BIN_CAT} ${.CURDIR}/common.sh | \
	${BIN_SED} ${SED_OPTS} | \
	${BIN_SED} ${SED_OPTS_BIN} > \
	${.OBJDIR}/${.TARGET}


# The tcc script is special
tcc-special:
	${BIN_CAT} ${.CURDIR}/tcc.sh | \
	${BIN_SED} ${SED_OPTS} | \
	${BIN_SED} ${SED_OPTS_BIN} > \
	${.OBJDIR}/tcc



SED_OPTS=	\
		-e "s|-TENDRA_BASEDIR-|${INSTALL_DIR}|g" \
		-e "s|-TENDRA_VERSION-|${VER_TENDRA}|g" \
		-e "s|-BIN_RUN-|${.TARGET}|g"

SED_OPTS_BIN=	\
		-e "s|-BIN_SH-|${BIN_SH}|g" \
		-e "s|-BIN_ECHO-|${BIN_ECHO}|g"


CLEANFILES=	${WRAPPERS:R} tcc.sh

.include "${.CURDIR}/../../mk/base/tendra.prog.mk"
