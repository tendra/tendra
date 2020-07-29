# Copyright 2010-2011, The TenDRA Project.
#
# See doc/copyright/ for the full copyright terms.


.if !defined(_TENDRA_DOC_MK_)
_TENDRA_DOC_MK_=1

.include <tendra.base.mk>
.include <tendra.functions.mk>


# TenDRA document processing.
#
# There are three user-specified parameters intended to be passed from the
# command line:
#
#   ${HTML}     - Output to HTML, instead of XHTML
#   ${WEBSITE}  - Output for website use (central CSS & javascript)
#
# Makfile-facing source parameters are:
#
#   ${DOC} - The source document. Typically set to ${.CURDIR:T}
#   ${MAN} - An optional manpage name and section. For example, "tld.1"
#
# Output is chunked into multiple pages if neccessary. Dependencies on images
# are identified automatically from the document itself.
#
# Manpages are also dealt with here, as we render those to HTML as well as to
# roff.


.if defined(MAN)
DOC=	${MAN}
.endif # defined(MAN)

.if defined(MAN)
_PREFIX_HTML=	${PREFIX_HTMLMAN}
.else
_PREFIX_HTML=	${PREFIX_HTMLDOC}
.endif # defined(MAN)

.if !defined(WEBSITE)
_PREFIX_HTML:=	"${_PREFIX_HTML}/${BASE_DIR:T}"
.endif

DOC_PREFIX?=	${BASE_DIR:T}

.if defined(WEBSITE) && !defined(MAN)
DOC_OUT:=	${DOC_PREFIX}-${DOC}
.else
DOC_OUT:=	${DOC}
.endif

. if defined(HTML)
DOC_EXT=	html
. else
DOC_EXT=	xhtml
. endif # defined(HTML)

. if defined(WEBSITE)
DOC_BASE=	http://www.tendra.org/
. else
DOC_BASE=	.
. endif	# defined(WEBSITE)

XMLOPTS+=	--nonet --xinclude
XMLOPTS+=	--path '${DTD_DIR}'

XSLTOPTS+=    --nomkdir
XMLLINTOPTS+= --loaddtd --valid

XSLTPARAMS+=	--stringparam tendra.base   '${DOC_BASE}'
XSLTPARAMS+=	--stringparam tendra.ext    '${DOC_EXT}'

XSLT_DIR=	${BASE_DIR}/shared/xsl
CSS_DIR=	${BASE_DIR}/shared/css
JS_DIR= 	${BASE_DIR}/shared/js
DTD_DIR= 	${BASE_DIR}/shared/dtd

XSLT_ROFF=	${XSLT_DIR}/roff/docbook.xsl
XSLT_HTML=	${XSLT_DIR}/${DOC_EXT}/minidocbook/main.xsl

XSLT_IMGS=	${XSLT_DIR}/support/docbook-images.xsl

DOC_MAN=	${MAN}
DOC_SRC=	${DOC}.xml
DOC_INDEX=	index.${DOC_EXT}
DOC_CSS=	css
DOC_JS= 	js

DOC_IMGDEPS!=	${XSLTPROC} ${XMLOPTS} ${XSLTOPTS} ${XSLT_IMGS} ${DOC_SRC}


#
# (X)HTML output
#
${OBJ_DDIR}/${DOC}/${DOC_INDEX}: ${DOC_SRC}
	@${CONDCREATE} "${OBJ_DDIR}/${DOC}"
	@${ECHO} "==> Transforming ${WRKDIR}/${DOC}"
	${XSLTPROC} ${XMLOPTS} ${XSLTOPTS} ${XSLTPARAMS} -o ${.TARGET:H}/ ${XSLT_HTML} ${.ALLSRC}

.if defined(MAN)
${OBJ_DDIR}/${DOC}/${DOC_MAN}: ${DOC_SRC}
	@${CONDCREATE} "${OBJ_DDIR}"
	@${ECHO} "==> Transforming ${WRKDIR}/${MAN}"
	${XSLTPROC} ${XMLOPTS} ${XSLTOPTS} -o ${.TARGET} ${XSLT_ROFF} ${.ALLSRC}
.endif


#
# CSS and Javascript
#
# TODO: use @${REPLICATE} from functions.mk, find(1) style
.if !defined(WEBSITE)
${OBJ_DDIR}/${DOC}/${DOC_CSS}: ${CSS_DIR}
	@${CONDCREATE} "${.TARGET}"
	@${ECHO} "==> Copying Stylesheets for ${WRKDIR}/${DOC}"
	cp ${CSS_DIR}/*.css ${.TARGET}

${OBJ_DDIR}/${DOC}/${DOC_JS}: ${JS_DIR}
	@${CONDCREATE} "${.TARGET}"
	@${ECHO} "==> Copying Javascript for ${WRKDIR}/${.ALLSRC:T}"
	cp ${JS_DIR}/*.js ${.TARGET}
.endif	# !defined(WEBSITE)



#
# User-facing targets
#

all:: ${OBJ_DDIR}/${DOC}/${DOC_INDEX}
.if !defined(WEBSITE)
all:: ${OBJ_DDIR}/${DOC}/${DOC_CSS} ${OBJ_DDIR}/${DOC}/${DOC_JS}
.endif
.if defined(MAN)
all:: ${OBJ_DDIR}/${DOC}/${DOC_MAN}
.endif
.if defined(DOC_IMGDEPS)
all:: ${DOC_IMGDEPS}
.endif


clean::
	${RMDIR} ${OBJ_DDIR}/${DOC}


install:: all
	@${CONDCREATE} "${_PREFIX_HTML}/${DOC_OUT}"
.if !defined(WEBSITE)
	@${CONDCREATE} "${_PREFIX_HTML}/${DOC_OUT}/${DOC_JS}"
	@${CONDCREATE} "${_PREFIX_HTML}/${DOC_OUT}/${DOC_CSS}"
	cp ${OBJ_DDIR}/${DOC}/${DOC_JS}/*.js   "${_PREFIX_HTML}/${DOC_OUT}/${DOC_JS}/"
	cp ${OBJ_DDIR}/${DOC}/${DOC_CSS}/*.css "${_PREFIX_HTML}/${DOC_OUT}/${DOC_CSS}/"
.endif
	cp ${OBJ_DDIR}/${DOC}/*.${DOC_EXT} "${_PREFIX_HTML}/${DOC_OUT}/"


test:: ${DOC_SRC}
	@${ECHO} "==> Validating ${.ALLSRC}"
	${XMLLINT} ${XMLOPTS} --dtdattr ${.ALLSRC} \
	| ${XMLLINT} ${XMLOPTS} ${XMLLINTOPTS} --noout -


.endif
