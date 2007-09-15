# $Id$

NAME = devguide

DOCTOOLS_BASE ?= ../../build

INSTALL = install

include $(DOCTOOLS_BASE)/docs.mk

install: all
	${INSTALL} -m 755 -d ${DOCDIR}/sid/${NAME}-single
	${INSTALL} -m 644 ../xhtml/${NAME}-single/* ${DOCDIR}/sid/${NAME}-single/
	${INSTALL} -m 755 -d ${DOCDIR}/sid/${NAME}
	${INSTALL} -m 644 ../xhtml/${NAME}/* ${DOCDIR}/sid/${NAME}/

