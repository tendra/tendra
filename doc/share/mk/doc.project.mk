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


# Image processing (contains code used by the doc.<format>.mk files, so must
# be listed first).
.include "doc.images.mk"

.if defined(DOC)
.include "doc.docbook.mk"
.endif

.include "doc.install.mk"

# Subdirectory glue.
.include "doc.subdir.mk"
