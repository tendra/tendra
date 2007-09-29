# $Id$

# This is a placeholder for tendra-doc to override.
DOCTOOLS_BASE ?= ../build

# For tendra-doc; ignored when standalone
COMPONENT = calculus

PASSTHROUGH = DOCTOOLS_BASE=../$(DOCTOOLS_BASE) COMPONENT=$(COMPONENT)


all:
	cd userguide && $(MAKE) all $(PASSTHROUGH) SECTION=user/guides
	cd man && $(MAKE) all pdf $(PASSTHROUGH) SECTION=user/man

clean:
	cd userguide && $(MAKE) clean $(PASSTHROUGH) SECTION=user/guides
	cd man && $(MAKE) clean $(PASSTHROUGH) SECTION=user/man

