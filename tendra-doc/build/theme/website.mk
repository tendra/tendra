# $Id$
#
# Resource location for documents deployed under the TenDRA website. These
# documents share their resources with the website itself in order to minimize
# the amount of duplicated files which would otherwise be downloaded.

RESOURCES =
CSSFILE = http://www.tendra.org/css/docs/docs.css

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

DOCSINSTALLDIR = doc/install/${THEMEFILENAME}/${SECTION}

include $(THEME)/common.mk

# Inter-document links
# We don't have a glossary up and running quite yet
DOCTOOLS_GLOSSFILE ?=
DOCTOOLS_DOCSDIR ?= ../../../../

