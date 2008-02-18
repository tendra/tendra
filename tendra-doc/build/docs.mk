# Centralised variables for TenDRA documentation. This is to avoid repetitions
# in each document's Makefile.
#
# $Id$

PROJECT_NAME = TenDRA Documentation
PROJECT_URL = http://docs.tendra.org/

# DOCTOOLS_BASE points to build/ - the directory this file is in.
DOCTOOLS_BASE ?= ../../build
THEMEDIR ?= $(DOCTOOLS_BASE)
THEMENAME ?= theme
THEMEFILENAME ?= website

# Assuming we generate all images
CLEAN_EXTRA ?= $(XHTMLIMAGES)
PREREQUSITES ?= $(XHTMLIMAGES)

DOCSINSTALLDIR ?= install
XHTMLDIR ?= $(DOCTOOLS_BASE)/../$(DOCSINSTALLDIR)
PDFDIR ?= $(DOCTOOLS_BASE)/../$(DOCSINSTALLDIR)

# XXX Workaround. See docbook.mk
DOCTOOLSBASE_FROM_PDFDIR ?= ../build

# docbook.mk doesn't play nice with the SUBDIRS mechanism
.if defined(SUBDIR)

_SUBDIR: .USE
. if !empty(SUBDIR)
.  for dir in ${SUBDIR}
	@echo "==> ${.CURDIR:T}/${dir}"
	@cd ${.CURDIR}/${dir} && ${MAKE} DOCTOOLS_BASE=../${DOCTOOLS_BASE} SECTION=${.CURDIR:T} ${.TARGET}
.  endfor
. endif

# These targets exist when using the SUBDIR mechanism
POSSIBLE_SUBDIR_TARGETS ?= all clean

.for target in ${POSSIBLE_SUBDIR_TARGETS}
${target}: _SUBDIR
.endfor

.else
include $(DOCTOOLS_BASE)/doctools/Mk/docbook.mk
.endif
