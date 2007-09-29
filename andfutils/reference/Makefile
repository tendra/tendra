# $Id$

# This is a placeholder for tendra-doc to override.
DOCTOOLS_BASE ?= ../build

# For tendra-doc; ignored when standalone
SECTION = reference

all:
	cd diagnostic && $(MAKE) all DOCTOOLS_BASE=../$(DOCTOOLS_BASE) SECTION=$(SECTION)
	cd guide && $(MAKE) all DOCTOOLS_BASE=../$(DOCTOOLS_BASE) SECTION=$(SECTION)
	cd register && $(MAKE) all DOCTOOLS_BASE=../$(DOCTOOLS_BASE) SECTION=$(SECTION)
	cd specification && $(MAKE) all DOCTOOLS_BASE=../$(DOCTOOLS_BASE) SECTION=$(SECTION)

clean:
	cd diagnostic && $(MAKE) clean DOCTOOLS_BASE=../$(DOCTOOLS_BASE) SECTION=$(SECTION)
	cd guide && $(MAKE) clean DOCTOOLS_BASE=../$(DOCTOOLS_BASE) SECTION=$(SECTION)
	cd register && $(MAKE) clean DOCTOOLS_BASE=../$(DOCTOOLS_BASE) SECTION=$(SECTION)
	cd specification && $(MAKE) clean DOCTOOLS_BASE=../$(DOCTOOLS_BASE) SECTION=$(SECTION)

