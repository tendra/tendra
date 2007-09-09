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
XHTMLDIR ?= $(DOCTOOLS_BASE)/../$(DOCSINSTALLDIR)
PDFDIR ?= $(DOCTOOLS_BASE)/../$(DOCSINSTALLDIR)

# TODO set theme etc

# XXX Workaround. See docbook.mk
DOCTOOLSBASE_FROM_PDFDIR ?= ../build

include $(DOCTOOLS_BASE)/doctools/Mk/docbook.mk

