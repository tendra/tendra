#
# $TenDRA: doc.docbook.mk 2447 2006-03-23 21:15:51Z verm $

DOCBOOKSUFFIX?= xml

MASTERDOC?=	${.CURDIR}/${DOC}.${DOCBOOKSUFFIX}

# general variables
PREFIX?=	/usr/local

XSL_HTML?=			${DOC_PREFIX}/share/xsl/html.xsl
XSL_FO?=			${DOC_PREFIX}/share/xsl/fo.xsl
XSL_CHUNK?=			${DOC_PREFIX}/share/xsl/chunk.xsl
XSL_MAN?=			${DOC_PREFIX}/share/xsl/man.xsl

XMLLINT?=			xmllint
XMLLINT_FLAGS?=		--path ${DOC_PREFIX}/share/includes:${DOC_PREFIX}/share/ent:${DOC_PREFIX}/share/xsl --load-trace --nonet --xinclude
XMLLINT_CATALOG?=	file:///${.CURDIR}/${DOC_PREFIX}/share/xsl/catalog.xml


JAR_SAXON?=			/usr/local/share/java/classes/saxon.jar
JAR_SAXON_EXT?=		/usr/local/share/xsl/docbook/extensions/saxon653.jar
JAR_RESOLVER?=		/usr/local/share/java/classes/resolver.jar
TENDRA_XSL_CP?=		${DOC_PREFIX}/share/xsl
SAXON_EXT_OPTS?=	use.extensions=1 tablecolumns.extension=0 fop.extensions=1



JAVA?=	java
JAVA_FLAGS?=		-cp "${JAR_SAXON}:${JAR_SAXON_EXT}:${JAR_RESOLVER}:${TENDRA_XSL_CP}" \
					com.icl.saxon.StyleSheet \
					-x org.apache.xml.resolver.tools.ResolvingXMLReader \
					-y org.apache.xml.resolver.tools.ResolvingXMLReader \
					-r org.apache.xml.resolver.tools.CatalogResolver -u


CSS_FILE?=	${DOC_PREFIX}/share/misc/docbook.css
CSS_SHEET?=	docbook.css


# fop -fo book.fo -pdf book.pdf
FOP?=				fop


RM?=		rm
BZIP2?=		-9
BZIP2_CMD?=	bzip2 -qf ${BZIP2}
TAR?=		tar
TIDY?=		tidy
TIDYOPTS?=	-i -m -raw -preserve -f /dev/null ${TIDYFLAGS}
XARGS?=		xargs

ZIP?=		-9
ZIP_CMD?=	zip -j ${ZIP}

# html-> text conversion
HTML2TXTOPTS?=	-dump ${HTML2TXTFLAGS}
HTML2PDB?=	iSiloBSD
HTML2PDBOPTS?=	-y -d0 -Idef ${HTML2PDBFLAGS}

.if exists(${PREFIX}/bin/elinks)
HTML2TXT?=	elinks
.else
HTML2TXT?=	links
.endif



#.if defined(TWO_SIDE)
#.endif


#.if defined(TRACE)
#.endif



.for _curformat in ${FORMATS}

_cf=${_curformat}

_docs+= ${DOC}.${_curformat}
CLEANFILES+=	${DOC}.${_curformat}

.if ${_cf} == "html-split"
_docs+=		index.html HTML.manifest ln*.html
CLEANFILES+=	$$([ -f HTML.manifest ] && ${XARGS} < HTML.manifest) \
		HTML.manifest ln*.html ${IMAGES_PNG} PLIST.${_curformat} \
		${CSS_SHEET}

.elif ${_cf} == "html"
CLEANFILES+=	${IMAGES_PNG} ${CSS_SHEET}

.elif ${_cf} == "html-split.tar"
CLEANFILES+=	$$([ -f HTML.manifest ] && ${XARGS} < HTML.manifest) \
		HTML.manifest ln*.html ${IMAGES_PNG} PLIST.${_curformat} \
		${CSS_SHEET}

.elif ${_cf} == "html.tar"
CLEANFILES+=	${DOC}.html ${IMAGES_PNG} ${CSS_SHEET}

.elif ${_cf} == "txt"
CLEANFILES+=	${DOC}.html-text

.elif ${_cf} == "dvi"
CLEANFILES+=	${DOC}.aux ${DOC}.log ${DOC}.tex ${IMAGES_EPS}

.elif ${_cf} == "pdf"
CLEANFILES+=	${DOC}.fo ${LOCAL_IMAGES_EPS}
.endif

.endfor


all: ${DEPEND_SRC} ${_docs}

# All document sources need xinclude subsitution to create the master file.
SRCS+=	${DOC}.xinc
CLEANFILES+=	${DOC}.xinc


# DEPENDANCY FILES.
# Xinclude --------------------------------------------------------------
${DOC}.xinc: ${DOC}.xml
	XML_CATALOG_FILES="${XMLLINT_CATALOG}" \
	${XMLLINT} ${XMLLINT_FLAGS} -o ${DOC}.xinc ${DOC}.xml

# FO ---------------------------------------------------------------------
${DOC}.fo: ${SRCS}
	${JAVA} \
	${JAVA_FLAGS} \
	-u -o ${DOC}.fo ${DOC}.xinc ${XSL_FO} ${SAXON_EXT_OPTS}


# TARGETS.
# PDF --------------------------------------------------------------------
${DOC}.pdf: ${LOCAL_IMAGES_EPS} ${DOC}.fo
	${FOP} \
	-fo ${DOC}.fo \
	-pdf ${DOC}.pdf	


# HTML -------------------------------------------------------------------
${DOC}.html: ${SRCS} ${LOCAL_IMAGES_PNG} ${CSS_SHEET} ${DOC}.xinc
	${JAVA} \
	${JAVA_FLAGS} \
	-u -o ${DOC}.html ${DOC}.xinc ${XSL_HTML} ${SAXON_EXT_OPTS}
.if !defined(NO_TIDY)
	-${TIDY} ${TIDYOPTS} ${.TARGET}
	-${TIDY} ${TIDYOPTS} ${.TARGET}
.endif


# MAN -------------------------------------------------------------------
${DOC}.man: ${SRCS} ${DOC}.xinc
	${JAVA} \
	${JAVA_FLAGS} \
	-u -o ${DOC}.man ${DOC}.xinc ${XSL_MAN} ${SAXON_EXT_OPTS}


# HTML-SPLIT -------------------------------------------------------------
index.html HTML.manifest: ${SRCS} ${LOCAL_IMAGES_PNG} \
			  ${INDEX_SGML} ${HTML_SPLIT_INDEX} ${CSS_SHEET}
	${JADE} -V html-manifest ${HTMLOPTS} -ioutput.html.images \
		${JADEOPTS} -t sgml ${MASTERDOC}
.if !defined(NO_TIDY)
	-${TIDY} ${TIDYOPTS} $$(${XARGS} < HTML.manifest)
	-${TIDY} ${TIDYOPTS} $$(${XARGS} < HTML.manifest)
.endif


# COMPRESSED TARGETS -----------------------------------------------------
${DOC}.html-split.tar: HTML.manifest \
		       ${LOCAL_IMAGES_PNG} ${CSS_SHEET}
	${TAR} cf ${.TARGET} $$(${XARGS} < HTML.manifest) \
		${IMAGES_PNG} ${CSS_SHEET:T}

${DOC}.html.tar: ${DOC}.html  \
		 ${LOCAL_IMAGES_PNG} ${CSS_SHEET}
	${TAR} cf ${.TARGET} ${DOC}.html \
		 ${IMAGES_PNG} ${CSS_SHEET:T}

${DOC}.tar: ${SRCS} ${LOCAL_IMAGES} ${CSS_SHEET}
	${TAR} cf ${.TARGET} -C ${.CURDIR} ${SRCS} \
		-C ${.OBJDIR} ${IMAGES} ${CSS_SHEET:T}


# MISC --------------------------------------------------------------------
${CSS_SHEET}:
	cat ${CSS_FILE} > ${.CURDIR}/${.TARGET} 
