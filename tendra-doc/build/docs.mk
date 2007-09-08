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

XHTMLDIR ?= $(DOCTOOLS_BASE)/../install
PDFDIR ?= $(DOCTOOLS_BASE)/../install

# TODO set theme etc

# XXX Workaround. See docbook.mk
DOCTOOLSBASE_FROM_PDFDIR ?= ../build

include $(DOCTOOLS_BASE)/doctools/Mk/docbook.mk

