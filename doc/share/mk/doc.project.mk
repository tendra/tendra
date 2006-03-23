# $TenDRA$

MAINTAINER?=	docs@ten15.org

# Master list of known target formats.  The doc.<format>.mk files implement 
# the code to convert from their source format to one or more of these target
# formats
# doc.docbook.ml
#ALL_FORMATS=	html html.tar html-split html-split.tar txt rtf ps pdf tex dvi tar pdb
ALL_FORMATS=	html html-split html-split.tar txt pdf


.MAIN: all

all: _SUBDIRUSE


# Image processing (contains code used by the doc.<format>.mk files, so must
# be listed first).

.if defined(DOC)
.include "doc.images.mk"
.include "doc.docbook.mk"
.include "doc.install.mk"
.endif


clean: _SUBDIRUSE
.if defined(CLEANFILES) && !empty(CLEANFILES)
	${RM} -f ${CLEANFILES}
.endif


cleanall:
	${MAKE} FORMATS="${ALL_FORMATS}" clean


# Subdirectory glue.

_SUBDIRUSE: .USE
.for entry in ${SUBDIR}
	@${ECHODIR} "===> ${DIRPRFX}${entry}"
	cd ${.CURDIR}/${entry} && \
	${MAKE} ${.TARGET} DIRPRFX=${DIRPRFX}${entry}/
.endfor
