# $Id$

# This is a placeholder for tendra-doc to override.
DOCTOOLS_BASE ?= ../build

# For tendra-doc; ignored when standalone
COMPONENT = lexi

PASSTHROUGH = DOCTOOLS_BASE=../$(DOCTOOLS_BASE) COMPONENT=$(COMPONENT)

all:
	cd guide && $(MAKE) all $(PASSTHROUGH) SECTION=user/guides
	cd man && $(MAKE) all pdf $(PASSTHROUGH) SECTION=user/man

clean:
	cd guide && $(MAKE) clean $(PASSTHROUGH) SECTION=user/guides
	cd man && $(MAKE) clean $(PASSTHROUGH) SECTION=user/man

install:
	cd guide && ${MAKE} install $(PASSTHROUGH) SECTION=user/guides
	cd man && ${MAKE} install $(PASSTHROUGH) SECTION=user/man

