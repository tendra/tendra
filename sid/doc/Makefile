# $Id$

# This is a placeholder for tendra-doc to override.
DOCTOOLS_BASE ?= ../build

# For tendra-doc; ignored when standalone
COMPONENT = sid

PASSTHROUGH = DOCTOOLS_BASE=../$(DOCTOOLS_BASE) COMPONENT=$(COMPONENT)

all:
	cd guide && ${MAKE} all $(PASSTHROUGH) SECTION=user/guides
	cd devguide && ${MAKE} all $(PASSTHROUGH) SECTION=developer/guides
	cd changelog && ${MAKE} all $(PASSTHROUGH) SECTION=user/changelog
	cd man && ${MAKE} all pdf $(PASSTHROUGH) SECTION=user/man

clean:
	cd guide && ${MAKE} clean $(PASSTHROUGH) SECTION=user/guides
	cd devguide && ${MAKE} clean $(PASSTHROUGH) SECTION=developer/guides
	cd changelog && ${MAKE} clean $(PASSTHROUGH) SECTION=user/changelog
	cd man && ${MAKE} clean $(PASSTHROUGH) SECTION=user/man

# TODO This should be moved to doctool's makefile somehow
install:
	cd guide && ${MAKE} install $(PASSTHROUGH) SECTION=user/guides
	cd devguide && ${MAKE} install $(PASSTHROUGH) SECTION=developer/guides
	cd changelog && ${MAKE} install $(PASSTHROUGH) SECTION=user/changelog
	cd man && ${MAKE} install $(PASSTHROUGH) SECTION=user/man

