# TenDRA make documentation infrastructure
#
# $Id$

.if !defined(_TENDRA_WORK_DOC_MK_)
_TENDRA_WORK_DOC_MK_=1

.include <tendra.base.mk>
.include <tendra.functions.mk>


# TenDRA document processing.
#
# There are two user-specified parameters intended to be passed from the
# command line:
#
#   ${HTML}    - Output to HTML, instead of XHTML
#   ${WEBSITE} - Output for website use (central CSS & javascript)
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


.if "${MAN}" != ""
DOC=	${MAN}
.endif # "${MAN}" != ""

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

XSLTOPTS+=	--xinclude --nomkdir --nonet

XSLTPARAMS+=	--stringparam tendra.base   '${DOC_BASE}'
XSLTPARAMS+=	--stringparam tendra.chunk  '${DOC_CHUNK}'
XSLTPARAMS+=	--stringparam tendra.method '${DOC_EXT:S/xhtml/xml/}'
XSLTPARAMS+=	--stringparam tendra.ext    '${DOC_EXT}'

XSLT_DIR=	${BASE_DIR}/doc/xsl
CSS_DIR=	${BASE_DIR}/doc/css
JS_DIR= 	${BASE_DIR}/doc/js

XSLT_HTML_SINGLE= 	${XSLT_DIR}/${DOC_EXT}/docbook-single.xsl
XSLT_HTML_CHUNKED=	${XSLT_DIR}/${DOC_EXT}/docbook-chunked.xsl
XSLT_ROFF=         	${XSLT_DIR}/roff/docbook.xsl

XSLT_EXT=	${XSLT_DIR}/support/xslt-fileext.xsl
XSLT_IMGS=	${XSLT_DIR}/support/docbook-images.xsl
XSLT_CHUNK=	${XSLT_DIR}/support/docbook-needschunking.xsl

DOC_MAN=	${MAN}
DOC_SRC=	${DOC}.xml
DOC_INDEX=	index.${DOC_EXT}
DOC_SINGLE=	single.${DOC_EXT}
DOC_CSS=	css
DOC_JS= 	js
DOC_IMAGES= 	images

DOC_IMGDEPS!=	${XSLTPROC} ${XSLTOPTS} ${XSLT_IMGS}  ${DOC_SRC}
DOC_CHUNK!=	${XSLTPROC} ${XSLTOPTS} ${XSLT_CHUNK} ${DOC_SRC}


#
# (X)HTML output
#
${OBJ_DDIR}/${DOC}/${DOC_INDEX}: ${DOC_SRC}
	@${CONDCREATE} "${OBJ_DDIR}/${DOC}"
.if ${DOC_CHUNK}
	@${ECHO} "==> Transforming ${WRKDIR}/${DOC} (multiple pages)"
	${XSLTPROC} ${XSLTOPTS} ${XSLTPARAMS} -o ${.TARGET:H}/${DOC_SINGLE} ${XSLT_HTML_SINGLE}  ${.ALLSRC}
	${XSLTPROC} ${XSLTOPTS} ${XSLTPARAMS} -o ${.TARGET:H}/              ${XSLT_HTML_CHUNKED} ${.ALLSRC}
.else
	@${ECHO} "==> Transforming ${WRKDIR}/${DOC} (single page)"
	${XSLTPROC} ${XSLTOPTS} ${XSLTPARAMS} -o ${.TARGET}                 ${XSLT_HTML_SINGLE}  ${.ALLSRC}
.endif

.if defined(MAN)
${OBJ_DDIR}/${DOC}/${DOC_MAN}: ${DOC_SRC}
	@${CONDCREATE} "${OBJ_DDIR}"
	@${ECHO} "==> Transforming ${WRKDIR}/${MAN}"
	${XSLTPROC} ${XSLTOPTS} -o ${.TARGET} ${XSLT_ROFF} ${.ALLSRC}
.endif


#
# Images
#
.for img in ${DOC_IMGDEPS}
. if exists(${img})
${OBJ_DDIR}/${DOC}/${img}: ${img}
	@${ECHO} "==> Copying raster image ${WRKDIR}/${img:T}"
	@${CONDCREATE} ${OBJ_DDIR}/${DOC}/${img:H}
	cp ${.ALLSRC} ${.TARGET}
. elif exists(${img:R}.dia)
${OBJ_DDIR}/${DOC}/${img}: ${img:R}.dia
	@${ECHO} "==> Rendering vector image ${WRKDIR}/${img:T}"
	@${CONDCREATE} ${OBJ_DDIR}/${DOC}/${img:H}
	${DIA} -e ${.TARGET} -t ${img:E} ${.ALLSRC}
. elif exists(${img:R}.dot)
${OBJ_DDIR}/${DOC}/${img}: ${img:R}.dot
	@${ECHO} "==> Rendering vector image ${WRKDIR}/${img:T}"
	@${CONDCREATE} ${OBJ_DDIR}/${DOC}/${img:H}
	${DOT} -o ${.TARGET} ${.ALLSRC}
. else
.BEGIN:
	@${ECHO} 'unrecognised image dependency: ${WRKDIR}/${img:T}'
	@${EXIT} 1;
. endif
.endfor


#
# CSS and Javascript
#
# TODO: use @${REPLICATE} from functions.mk, find(1) style
.if !defined(WEBSITE)
${OBJ_DDIR}/${DOC}/${DOC_CSS}: ${CSS_DIR}
	@${CONDCREATE} "${.TARGET}"
	@${ECHO} "==> Copying Stylesheets for ${WRKDIR}/${DOC}"
	cp -rp ${.ALLSRC} ${.TARGET:H}

${OBJ_DDIR}/${DOC}/${DOC_JS}: ${JS_DIR}
	@${CONDCREATE} "${.TARGET}"
	@${ECHO} "==> Copying Javascript for ${WRKDIR}/${.ALLSRC:T}"
	cp -rp ${.ALLSRC} ${.TARGET:H}
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
.if "${DOC_IMGDEPS}" != ""
all:: ${DOC_IMGDEPS:C/^/${OBJ_DDIR}\/${DOC}\//}
.endif


clean::
	${REMOVE} -r ${OBJ_DDIR}/${DOC}


install:: all



.endif	# !defined(_TENDRA_WORK_DOC_MK_)
