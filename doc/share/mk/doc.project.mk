# $TenDRA$

DOCFORMAT?=	docbook
MAINTAINER?=	docs@ten15.org

# Master list of known target formats.  The doc.<format>.mk files implement 
# the code to convert from their source format to one or more of these target
# formats
ALL_FORMATS=	html html.tar html-split html-split.tar txt rtf ps pdf tex dvi tar pdb

# User-modifiable
#LOCALBASE?=	/usr/local
PREFIX?=	/usr/local
#PRI_LANG?=	en

CP?=		/bin/cp
CAT?=		/bin/cat
ECHO_CMD?=	echo
LN?=		/bin/ln
MKDIR?=		/bin/mkdir -p
RM?=		/bin/rm
MV?=		/bin/mv


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
