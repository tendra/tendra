#
# $TenDRA$

DOCBOOKSUFFIX?= sgml

MASTERDOC?=	${.CURDIR}/${DOC}.${DOCBOOKSUFFIX}

# general variables
PREFIX?=	/usr/local


# openjade settings
JADE?=		${PREFIX}/bin/openjade
JADECATALOG?=	${PREFIX}/share/sgml/openjade/catalog
NSGMLS?=	${PREFIX}/bin/onsgmls
JADEFLAGS+=	-V openjade
SX?=		${PREFIX}/bin/osx
DSLHTML?=	${DOC_PREFIX}/share/sgml/default.dsl
DSLPRINT?=	${DOC_PREFIX}/share/sgml/default.dsl
DSLPGP?=	${DOC_PREFIX}/share/sgml/pgp.dsl
FREEBSDCATALOG=	${DOC_PREFIX}/share/sgml/catalog
LANGUAGECATALOG=${DOC_PREFIX}/${LANGCODE}/share/sgml/catalog
ISO8879CATALOG=	${PREFIX}/share/sgml/iso8879/catalog
DOCBOOKCATALOG=	${PREFIX}/share/sgml/docbook/catalog
DSSSLCATALOG=	${PREFIX}/share/sgml/docbook/dsssl/modular/catalog
COLLATEINDEX=	${PREFIX}/share/sgml/docbook/dsssl/modular/bin/collateindex.pl
CATALOGS=	-c ${LANGUAGECATALOG} -c ${FREEBSDCATALOG} \
		-c ${DSSSLCATALOG} -c ${ISO8879CATALOG} \
		-c ${DOCBOOKCATALOG} -c ${JADECATALOG} \
		${EXTRA_CATALOGS:S/^/-c /g}
CSS_FILE?=	${DOC_PREFIX}/share/misc/docbook.css
CSS_SHEET?=	${CSS_FILE:T}
PDFTEX_DEF?=	${DOC_PREFIX}/share/web2c/pdftex.def
JADEOPTS=	${JADEFLAGS} ${SGMLFLAGS} ${CATALOGS}
KNOWN_FORMATS=	html html.tar html-split html-split.tar \
		txt rtf ps pdf tex dvi tar pdb
HTMLOPTS?=	-ioutput.html -d ${DSLHTML} ${HTMLFLAGS}
PRINTOPTS?=	-ioutput.print -d ${DSLPRINT} ${PRINTFLAGS}
# XXX: this a hack#, fix later.
SGMLFLAGS+=	-D ${.CURDIR}


# binaries
TAR?=		tar
XARGS?=		xargs
TEX?=		tex
LATEX?=		latex
PDFTEX?=	pdftex
TIDY?=		tidy
TIDYOPTS?=	-i -m -raw -preserve -f /dev/null ${TIDYFLAGS}
DVIPS?=		dvips
GZIP?=	-9
GZIP_CMD?=	gzip -qf ${GZIP}
BZIP2?=	-9
BZIP2_CMD?=	bzip2 -qf ${BZIP2}
ZIP?=	-9
ZIP_CMD?=	zip -j ${ZIP}
RM?=		rm

# html-> text conversion
HTML2TXTOPTS?=	-dump ${HTML2TXTFLAGS}
HTML2PDB?=	iSiloBSD
HTML2PDBOPTS?=	-y -d0 -Idef ${HTML2PDBFLAGS}

.if exists(${PREFIX}/bin/elinks)
HTML2TXT?=	elinks
.else
HTML2TXT?=	links
.endif




.if defined(BOOK_OUTPUT)
NICE_HEADERS=1
MIN_SECT_LABELS=0
TWO_SIDE=1
JUSTIFY=1
#WITH_FOOTNOTES=1
#GEN_INDEX=1
.endif

.if defined(JUSTIFY)
TEXCMDS+=	\RequirePackage{url}
PRINTOPTS+=	-ioutput.print.justify
.endif

.if defined(TWO_SIDE)
PRINTOPTS+=	-V %two-side% -ioutput.print.twoside
TEXCMDS+=	\def\PageTwoSide{1}
.endif

.if defined(NICE_HEADERS)
PRINTOPTS+=    -ioutput.print.niceheaders
.endif

.if defined(MIN_SECT_LABELS)
PRINTOPTS+=    -V minimal-section-labels
.endif

.if defined(TRACE)
TEXCMDS+=	\tracingstats=${TRACE}
.endif

.if defined(RLE)
PNMTOPSFLAGS+=	-rle
.endif


.if defined(PAPERSIZE)
DVIPSOPTS?=	-t ${PAPERSIZE:L} ${DVIPSFLAGS}
.endif





.for _curformat in ${FORMATS}
_cf=${_curformat}

.if ${_cf} == "html-split"
_docs+= index.html HTML.manifest ln*.html
CLEANFILES+= $$([ -f HTML.manifest ] && ${XARGS} < HTML.manifest) \
		HTML.manifest ln*.html ${IMAGES_PNG}
CLEANFILES+= PLIST.${_curformat}
.else
_docs+= ${DOC}.${_curformat}
CLEANFILES+= ${DOC}.${_curformat}
CLEANFILES+= PLIST.${_curformat}

.if ${_cf} == "html-split.tar"
CLEANFILES+= $$([ -f HTML.manifest ] && ${XARGS} < HTML.manifest) \
		HTML.manifest ln*.html ${IMAGES_PNG}
.elif ${_cf} == "html.tar"

CLEANFILES+= ${DOC}.html ${IMAGES_PNG} ${CSS_SHEET}

.elif ${_cf} == "html"
CLEANFILES+= ${DOC}.html ${IMAGES_PNG} ${CSS_SHEET}

.elif ${_cf} == "txt"
CLEANFILES+= ${DOC}.html-text

.elif ${_cf} == "dvi"
CLEANFILES+= ${DOC}.aux ${DOC}.log ${DOC}.tex ${IMAGES_EPS}

.elif ${_cf} == "tex"
CLEANFILES+= ${DOC}.aux ${DOC}.log ${IMAGES_EPS}

.elif ${_cf} == "ps"
CLEANFILES+= ${DOC}.aux ${DOC}.dvi ${DOC}.log ${DOC}.tex ${IMAGES_EPS}

.elif ${_cf} == "pdf"
CLEANFILES+= ${DOC}.aux ${DOC}.dvi ${DOC}.log ${DOC}.out ${DOC}.tex-pdf ${IMAGES_PDF}

.elif ${_cf} == "pdb"
_docs+= ${.CURDIR:T}.pdb
CLEANFILES+= ${.CURDIR:T}.pdb
.endif
.endif

.endfor


#
# Index generation
#
CLEANFILES+= 		${INDEX_SGML}

.if defined(GEN_INDEX) && defined(HAS_INDEX)
JADEFLAGS+=		-i chap.index
HTML_SPLIT_INDEX?=	html-split.index
HTML_INDEX?=		html.index
PRINT_INDEX?=		print.index
INDEX_SGML?=		index.sgml

CLEANFILES+= 		${HTML_SPLIT_INDEX} ${HTML_INDEX} ${PRINT_INDEX}
.endif




all: ${_docs}


# HTML-SPLIT -------------------------------------------------------------
index.html HTML.manifest: ${SRCS} ${LOCAL_IMAGES_PNG} \
			  ${INDEX_SGML} ${HTML_SPLIT_INDEX} ${CSS_SHEET}
	${JADE} -V html-manifest ${HTMLOPTS} -ioutput.html.images \
		${JADEOPTS} -t sgml ${MASTERDOC}
.if !defined(NO_TIDY)
	-${TIDY} ${TIDYOPTS} $$(${XARGS} < HTML.manifest)
	-${TIDY} ${TIDYOPTS} $$(${XARGS} < HTML.manifest)
.endif



# HTML -------------------------------------------------------------------
${DOC}.html: ${SRCS} ${LOCAL_IMAGES_PNG} \
	     ${INDEX_SGML} ${HTML_INDEX} ${CSS_SHEET}
	${JADE} -V nochunks ${HTMLOPTS} -ioutput.html.images \
		${JADEOPTS} -t sgml ${MASTERDOC} > ${.TARGET} || \
		(${RM} -f ${.TARGET} && false)
.if !defined(NO_TIDY)
	-${TIDY} ${TIDYOPTS} ${.TARGET}
	-${TIDY} ${TIDYOPTS} ${.TARGET}
.endif



# HTML-TEXT --------------------------------------------------------------
# Special target to produce HTML with no images in it.
${DOC}.html-text: ${SRCS} ${INDEX_SGML} ${HTML_INDEX}
	${JADE} -V nochunks ${HTMLOPTS} \
		${JADEOPTS} -t sgml ${MASTERDOC} > ${.TARGET} || \
		(${RM} -f ${.TARGET} && false)
.if !defined(NO_TIDY)
	-${TIDY} ${TIDYOPTS} ${.TARGET}
	-${TIDY} ${TIDYOPTS} ${.TARGET}
.endif

${DOC}.html-split.tar: HTML.manifest \
		       ${LOCAL_IMAGES_PNG} ${CSS_SHEET}
	${TAR} cf ${.TARGET} $$(${XARGS} < HTML.manifest) \
		${IMAGES_PNG} ${CSS_SHEET:T}

${DOC}.html.tar: ${DOC}.html  \
		 ${LOCAL_IMAGES_PNG} ${CSS_SHEET}
	${TAR} cf ${.TARGET} ${DOC}.html \
		 ${IMAGES_PNG} ${CSS_SHEET:T}



# TXT --------------------------------------------------------------------
${DOC}.txt: ${DOC}.html-text
	${HTML2TXT} ${HTML2TXTOPTS} ${.ALLSRC} > ${.TARGET}

# PDB --------------------------------------------------------------------

${DOC}.pdb: ${DOC}.html  ${LOCAL_IMAGES_PNG}
	${HTML2PDB} ${HTML2PDBOPTS} ${DOC}.html ${.TARGET}

${.CURDIR:T}.pdb: ${DOC}.pdb
	${LN} -f ${.ALLSRC} ${.TARGET}

.if defined(INSTALL_COMPRESSED) && !empty(INSTALL_COMPRESSED)
.for _curcomp in ${INSTALL_COMPRESSED}
${.CURDIR:T}.pdb.${_curcomp}: ${DOC}.pdb.${_curcomp}
	${LN} -f ${.ALLSRC} ${.TARGET}
.endfor
.endif



# RTF --------------------------------------------------------------------
${DOC}.rtf: ${SRCS} ${LOCAL_IMAGES_EPS}
	${JADE} -V rtf-backend ${PRINTOPTS} \
		${JADEOPTS} -t rtf -o ${.TARGET} ${MASTERDOC}

#
# This sucks, but there's no way round it.  The PS and PDF formats need
# to use different image formats, which are chosen at the .tex stage.  So,
# we need to create a different .tex file depending on our eventual output
# format, which will then lead on to a different .dvi file as well.
#

${DOC}.tex: ${SRCS} ${LOCAL_IMAGES_EPS} ${INDEX_SGML} ${PRINT_INDEX}
	${JADE} -V tex-backend ${PRINTOPTS} \
		${JADEOPTS} -t tex -o ${.TARGET} ${MASTERDOC}

${DOC}.tex-pdf: ${SRCS} ${IMAGES_PDF} ${INDEX_SGML} ${PRINT_INDEX}
	${RM} -f ${.TARGET}
	${CAT} ${PDFTEX_DEF} > ${.TARGET}
	${JADE} -V tex-backend ${PRINTOPTS} -ioutput.print.pdf \
		${JADEOPTS} -t tex -o /dev/stdout ${MASTERDOC} >> ${.TARGET}

${DOC}.dvi: ${DOC}.tex ${LOCAL_IMAGES_EPS}
	@${ECHO} "==> TeX pass 1/3"
	-${TEX} "&jadetex" '${TEXCMDS} \nonstopmode\input{${DOC}.tex}'
	@${ECHO} "==> TeX pass 2/3"
	-${TEX} "&jadetex" '${TEXCMDS} \nonstopmode\input{${DOC}.tex}'
	@${ECHO} "==> TeX pass 3/3"
	-${TEX} "&jadetex" '${TEXCMDS} \nonstopmode\input{${DOC}.tex}'

${DOC}.pdf: ${DOC}.tex-pdf ${IMAGES_PDF}
	@${ECHO} "==> PDFTeX pass 1/3"
	-${PDFTEX} "&pdfjadetex" '${TEXCMDS} \nonstopmode\input{${DOC}.tex-pdf}'
	@${ECHO} "==> PDFTeX pass 2/3"
	-${PDFTEX} "&pdfjadetex" '${TEXCMDS} \nonstopmode\input{${DOC}.tex-pdf}'
	@${ECHO} "==> PDFTeX pass 3/3"
	${PDFTEX} "&pdfjadetex" '${TEXCMDS} \nonstopmode\input{${DOC}.tex-pdf}'

${DOC}.ps: ${DOC}.dvi
	${DVIPS} ${DVIPSOPTS} -o ${.TARGET} ${.ALLSRC}

${DOC}.tar: ${SRCS} ${LOCAL_IMAGES} ${CSS_SHEET}
	${TAR} cf ${.TARGET} -C ${.CURDIR} ${SRCS} \
		-C ${.OBJDIR} ${IMAGES} ${CSS_SHEET:T}

${CSS_SHEET}:
	cat ${CSS_FILE} > ${.CURDIR}/${.TARGET} 
	



validate:
	${NSGMLS} -s ${SGMLFLAGS} ${CATALOGS} ${MASTERDOC}
