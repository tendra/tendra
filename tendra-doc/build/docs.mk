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
THEMEFILENAME ?= standalone

# Assuming we generate all images
CLEAN_EXTRA ?= $(XHTMLIMAGES)
PREREQUSITES ?= $(XHTMLIMAGES)

DOCSINSTALLDIR ?= install
XHTMLDIR ?= $(DOCTOOLS_BASE)/../$(DOCSINSTALLDIR)/$(SECTION)
PDFDIR ?= $(DOCTOOLS_BASE)/../$(DOCSINSTALLDIR)/$(SECTION)

# Externaled projects have less-specific names. Standalone applications have a
# neccessarily different structure for their documentation to tendra-doc. I'll
# take sid as an example. Standalone, it installs into $PREFIX/share/doc as
# sid/{userguide,devguide} - there is no need to include the component name
# in the documents' directories, since that is implicit in the heirachy.
#
# However, under tendra-doc the heirachy is divided by document type, not by
# component. Hence Sid installs into {user,developer}/guide/sid - alongside
# various other components.
#
# The component is expected to set $(SECTION) and $(COMPONENT) itself.
.ifdef COMPONENT
SOURCE := $(NAME).xml
NAME = $(COMPONENT)
.endif

# XXX Workaround. See docbook.mk
DOCTOOLSBASE_FROM_PDFDIR ?= ../build

include $(DOCTOOLS_BASE)/doctools/Mk/docbook.mk

