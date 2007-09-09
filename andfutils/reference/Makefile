# $Id$

# This is a placeholder for tendra-doc to override.
DOCTOOLS_BASE ?= ../build

all:
	cd diagnostic && $(MAKE) all DOCTOOLS_BASE=../$(DOCTOOLS_BASE)
	cd guide && $(MAKE) all DOCTOOLS_BASE=../$(DOCTOOLS_BASE)
	cd register && $(MAKE) all DOCTOOLS_BASE=../$(DOCTOOLS_BASE)
	cd specification && $(MAKE) all DOCTOOLS_BASE=../$(DOCTOOLS_BASE)

clean:
	cd diagnostic && $(MAKE) clean DOCTOOLS_BASE=../$(DOCTOOLS_BASE)
	cd guide && $(MAKE) clean DOCTOOLS_BASE=../$(DOCTOOLS_BASE)
	cd register && $(MAKE) clean DOCTOOLS_BASE=../$(DOCTOOLS_BASE)
	cd specification && $(MAKE) clean DOCTOOLS_BASE=../$(DOCTOOLS_BASE)

