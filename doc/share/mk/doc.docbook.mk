#
# $TenDRA$

DOCBOOKSUFFIX?= sgml

MASTERDOC?=	${.CURDIR}/${DOC}.${DOCBOOKSUFFIX}

# Which stylesheet type to use.  'dsssl' or 'xsl'
STYLESHEET_TYPE?=	dsssl

.if ${MACHINE_ARCH} != "i386"
OPENJADE=	yes
.endif

.if defined(OPENJADE)
JADE?=		${PREFIX}/bin/openjade
JADECATALOG?=	${PREFIX}/share/sgml/openjade/catalog
NSGMLS?=	${PREFIX}/bin/onsgmls
JADEFLAGS+=	-V openjade
SX?=		${PREFIX}/bin/osx
.else
JADE?=		${PREFIX}/bin/jade
JADECATALOG?=	${PREFIX}/share/sgml/jade/catalog
NSGMLS?=	${PREFIX}/bin/nsgmls
SX?=		${PREFIX}/bin/sx
.endif

DSLHTML?=	${DOC_PREFIX}/share/sgml/default.dsl
DSLPRINT?=	${DOC_PREFIX}/share/sgml/default.dsl
DSLPGP?=	${DOC_PREFIX}/share/sgml/pgp.dsl
FREEBSDCATALOG=	${DOC_PREFIX}/share/sgml/catalog
LANGUAGECATALOG=${DOC_PREFIX}/${LANGCODE}/share/sgml/catalog

ISO8879CATALOG=	${PREFIX}/share/sgml/iso8879/catalog

.if ${STYLESHEET_TYPE} == "dsssl"
DOCBOOKCATALOG=	${PREFIX}/share/sgml/docbook/catalog
.elif ${STYLESHEET_TYPE} == "xsl"
DOCBOOKCATALOG= ${PREFIX}/share/xml/docbook/catalog
.endif

DSSSLCATALOG=	${PREFIX}/share/sgml/docbook/dsssl/modular/catalog
COLLATEINDEX=	${PREFIX}/share/sgml/docbook/dsssl/modular/bin/collateindex.pl

XSLTPROC?=	${PREFIX}/bin/xsltproc
XSLHTML?=	${DOC_PREFIX}/share/xsl/freebsd-html.xsl
XSLHTMLCHUNK?=	${DOC_PREFIX}/share/xsl/freebsd-html-chunk.xsl
XSLFO?=		${DOC_PREFIX}/share/xsl/freebsd-fo.xsl

IMAGES_LIB?=

CATALOGS=	-c ${LANGUAGECATALOG} -c ${FREEBSDCATALOG} \
		-c ${DSSSLCATALOG} -c ${ISO8879CATALOG} \
		-c ${DOCBOOKCATALOG} -c ${JADECATALOG} \
		${EXTRA_CATALOGS:S/^/-c /g}
# XXX: this a hack#, fix later.
#SGMLFLAGS+=	-D ${CANONICALOBJDIR}
SGMLFLAGS+=	-D ${.CURDIR}

JADEOPTS=	${JADEFLAGS} ${SGMLFLAGS} ${CATALOGS}

KNOWN_FORMATS=	html html.tar html-split html-split.tar \
		txt rtf ps pdf tex dvi tar pdb

CSS_SHEET?=	${DOC_PREFIX}/share/misc/docbook.css
PDFTEX_DEF?=	${DOC_PREFIX}/share/web2c/pdftex.def

HTMLOPTS?=	-ioutput.html -d ${DSLHTML} ${HTMLFLAGS}

PRINTOPTS?=	-ioutput.print -d ${DSLPRINT} ${PRINTFLAGS}

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

PERL?=		/usr/bin/perl
PKG_CREATE?=	/usr/sbin/pkg_create
SORT?=		/usr/bin/sort
TAR?=		/usr/bin/tar
TOUCH?=		/usr/bin/touch
XARGS?=		/usr/bin/xargs

TEX?=		${PREFIX}/bin/tex
LATEX?=		${PREFIX}/bin/latex
PDFTEX?=	${PREFIX}/bin/pdftex
GROFF?=		groff
TIDY?=		${PREFIX}/bin/tidy
TIDYOPTS?=	-i -m -raw -preserve -f /dev/null ${TIDYFLAGS}
.if exists(${PREFIX}/bin/elinks)
HTML2TXT?=	${PREFIX}/bin/elinks
.else
HTML2TXT?=	${PREFIX}/bin/links
.endif
HTML2TXTOPTS?=	-dump ${HTML2TXTFLAGS}
HTML2PDB?=	${PREFIX}/bin/iSiloBSD
HTML2PDBOPTS?=	-y -d0 -Idef ${HTML2PDBFLAGS}
DVIPS?=		${PREFIX}/bin/dvips
.if defined(PAPERSIZE)
DVIPSOPTS?=	-t ${PAPERSIZE:L} ${DVIPSFLAGS}
.endif

GZIP?=	-9
GZIP_CMD?=	gzip -qf ${GZIP}
BZIP2?=	-9
BZIP2_CMD?=	bzip2 -qf ${BZIP2}
ZIP?=	-9
ZIP_CMD?=	${PREFIX}/bin/zip -j ${ZIP}

# ------------------------------------------------------------------------
#
# Look at ${FORMATS} and work out which documents need to be generated.
# It is assumed that the HTML transformation will always create a file
# called index.html, and that for every other transformation the name
# of the generated file is ${DOC}.format.
#
# ${_docs} will be set to a list of all documents that must be made
# up to date.
#
# ${CLEANFILES} is a list of files that should be removed by the "clean"
# target. ${COMPRESS_EXT:S/^/${DOC}.${_cf}.&/ takes the COMPRESS_EXT
# var, and prepends the filename to each listed extension, building a
# second list of files with the compressed extensions added.
#

# Note: ".for _curformat in ${KNOWN_FORMATS}" is used several times in
# this file. I know they could have been rolled together in to one, much
# larger, loop. However, that would have made things more complicated
# for a newcomer to this file to unravel and understand, and a syntax
# error in the loop would have affected the entire
# build/compress/install process, instead of just one of them, making it
# more difficult to debug.
#

# Note: It is the aim of this file that *all* the targets be available,
# not just those appropriate to the current ${FORMATS} and
# ${INSTALL_COMPRESSED} values.
#
# For example, if FORMATS=html and INSTALL_COMPRESSED=gz you could still
# type
#
#     make book.rtf.bz2
#
# and it will do the right thing. Or
#
#     make install-rtf.bz2
#
# for that matter. But don't expect "make clean" to work if the FORMATS
# and INSTALL_COMPRESSED variables are wrong.
#

.if ${.OBJDIR} != ${.CURDIR}
LOCAL_CSS_SHEET= ${.OBJDIR}/${CSS_SHEET:T}
.else
LOCAL_CSS_SHEET= ${CSS_SHEET:T}
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
CLEANFILES+= ${DOC}.html ${IMAGES_PNG}

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

.if (${LOCAL_CSS_SHEET} != ${CSS_SHEET}) && \
    (${_cf} == "html-split" || ${_cf} == "html-split.tar" || \
     ${_cf} == "html" || ${_cf} == "html.tar" || ${_cf} == "txt")
CLEANFILES+= ${LOCAL_CSS_SHEET} ${IMAGES_PNG}
.endif

.endfor


#
# Build a list of install-${format}.${compress_format} targets to be
# by "make install". Also, add ${DOC}.${format}.${compress_format} to
# ${_docs} and ${CLEANFILES} so they get built/cleaned by "all" and
# "clean".
#

.if defined(INSTALL_COMPRESSED) && !empty(INSTALL_COMPRESSED)
.for _curformat in ${FORMATS}
_cf=${_curformat}
.for _curcomp in ${INSTALL_COMPRESSED}

.if ${_cf} != "html-split" && ${_cf} != "html"
_curinst+= install-${_curformat}.${_curcomp}
_docs+= ${DOC}.${_curformat}.${_curcomp}
CLEANFILES+= ${DOC}.${_curformat}.${_curcomp}

.if  ${_cf} == "pdb"
_docs+= ${.CURDIR:T}.${_curformat}.${_curcomp}
CLEANFILES+= ${.CURDIR:T}.${_curformat}.${_curcomp}

.endif
.endif
.endfor
.endfor
.endif

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

.MAIN: all

all: ${_docs}

# XML --------------------------------------------------------------------

# sx generates a lot of (spurious) errors of the form "reference to
# internal SDATA entity ...".  So dump the errors to separate file, and
# grep for any other errors to show them to the user.
#
# Better approaches to handling this would be most welcome

${DOC}.xml: ${SRCS}
	echo '<!DOCTYPE book SYSTEM "/usr/local/share/xml/docbook/4.1.2/docbookx.dtd">' > ${DOC}.xml
	${SX} -xlower -xndata ${MASTERDOC} 2> .sxerr | tail -n +2 >> ${DOC}.xml 
	@-grep -v 'reference to internal SDATA entity' .sxerr

# HTML-SPLIT -------------------------------------------------------------

.if ${STYLESHEET_TYPE} == "dsssl"
index.html HTML.manifest: ${SRCS} ${LOCAL_IMAGES_LIB} ${LOCAL_IMAGES_PNG} \
			  ${INDEX_SGML} ${HTML_SPLIT_INDEX} ${LOCAL_CSS_SHEET}
	${JADE} -V html-manifest ${HTMLOPTS} -ioutput.html.images \
		${JADEOPTS} -t sgml ${MASTERDOC}
.elif ${STYLESHEET_TYPE} == "xsl"
index.html: ${DOC}.xml ${LOCAL_IMAGES_LIB} ${LOCAL_IMAGES_PNG} \
	${INDEX_SGML} ${HTML_SPLIT_INDEX} ${LOCAL_CSS_SHEET}
	${XSLTPROC} --param freebsd.output.html.images "'1'" ${XSLHTMLCHUNK} \
		${DOC}.xml
.endif
.if !defined(NO_TIDY)
	-${TIDY} ${TIDYOPTS} $$(${XARGS} < HTML.manifest)
.endif

# HTML -------------------------------------------------------------------

.if ${STYLESHEET_TYPE} == "dsssl"
${DOC}.html: ${SRCS} ${LOCAL_IMAGES_LIB} ${LOCAL_IMAGES_PNG} \
	     ${INDEX_SGML} ${HTML_INDEX} ${LOCAL_CSS_SHEET}
	${JADE} -V nochunks ${HTMLOPTS} -ioutput.html.images \
		${JADEOPTS} -t sgml ${MASTERDOC} > ${.TARGET} || \
		(${RM} -f ${.TARGET} && false)
.elif ${STYLESHEET_TYPE} == "xsl"
${DOC}.html: ${DOC}.xml ${LOCAL_IMAGES_LIB} ${LOCAL_IMAGES_PNG} \
	${INDEX_SGML} ${LOCAL_CSS_SHEET}     
	${XSLTPROC} --param freebsd.output.html.images "'1'" ${XSLHTML} \
		${DOC}.xml > ${.TARGET}
.endif
.if !defined(NO_TIDY)
	-${TIDY} ${TIDYOPTS} ${.TARGET}
.endif

# HTML-TEXT --------------------------------------------------------------

# Special target to produce HTML with no images in it.
.if ${STYLESHEET_TYPE} == "dsssl"
${DOC}.html-text: ${SRCS} ${INDEX_SGML} ${HTML_INDEX}
	${JADE} -V nochunks ${HTMLOPTS} \
		${JADEOPTS} -t sgml ${MASTERDOC} > ${.TARGET} || \
		(${RM} -f ${.TARGET} && false)
.elif ${STYLESHEET_TYPE} == "xsl"
${DOC}.html-text: ${DOC}.xml ${INDEX_SGML} ${HTML_INDEX}
	${XSLTPROC} --param freebsd.output.html.images "'0'" ${XSLHTML} \
		${DOC}.xml > ${.TARGET}
.endif
.if !defined(NO_TIDY)
	-${TIDY} ${TIDYOPTS} ${.TARGET}
.endif

${DOC}.html-split.tar: HTML.manifest ${LOCAL_IMAGES_LIB} \
		       ${LOCAL_IMAGES_PNG} ${LOCAL_CSS_SHEET}
	${TAR} cf ${.TARGET} $$(${XARGS} < HTML.manifest) \
		${LOCAL_IMAGES_LIB} ${IMAGES_PNG} ${CSS_SHEET:T}

${DOC}.html.tar: ${DOC}.html ${LOCAL_IMAGES_LIB} \
		 ${LOCAL_IMAGES_PNG} ${LOCAL_CSS_SHEET}
	${TAR} cf ${.TARGET} ${DOC}.html \
		${LOCAL_IMAGES_LIB} ${IMAGES_PNG} ${CSS_SHEET:T}

# TXT --------------------------------------------------------------------

${DOC}.txt: ${DOC}.html-text
	${HTML2TXT} ${HTML2TXTOPTS} ${.ALLSRC} > ${.TARGET}

# PDB --------------------------------------------------------------------

${DOC}.pdb: ${DOC}.html ${LOCAL_IMAGES_LIB} ${LOCAL_IMAGES_PNG}
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

${DOC}.tar: ${SRCS} ${LOCAL_IMAGES} ${LOCAL_CSS_SHEET}
	${TAR} cf ${.TARGET} -C ${.CURDIR} ${SRCS} \
		-C ${.OBJDIR} ${IMAGES} ${CSS_SHEET:T}




# ------------------------------------------------------------------------
#
# Validation targets
#

#
# Lets you quickly check that the document conforms to the DTD without
# having to convert it to any other formats
#

lint validate:
	${NSGMLS} -s ${SGMLFLAGS} ${CATALOGS} ${MASTERDOC}


# style sheet
.if ${LOCAL_CSS_SHEET} != ${CSS_SHEET}
${LOCAL_CSS_SHEET}: ${CSS_SHEET}
	${RM} -f ${.TARGET}
	${CAT} ${.ALLSRC} > ${.TARGET}
.if defined(CSS_SHEET_ADDITIONS)
	${CAT} ${.CURDIR}/${CSS_SHEET_ADDITIONS} >> ${.TARGET}
.endif
.endif

