# $Id$
# TODO: perhaps an extra-params variable, for:
#    <xsl:param name="css.decoration">0</xsl:param>
#    <xsl:param name="paper.type">A4</xsl:param>
#    <xsl:param name="section.autolabel">1</xsl:param>
#    <xsl:param name="section.label.includes.component.label">1</xsl:param>


NAME = guide

DOCTOOLS_BASE ?= ../../build


PREFIX ?= /usr/local
SHAREDIR ?= ${PREFIX}/share
DOCDIR ?= ${SHAREDIR}/doc

INSTALL = install

include $(DOCTOOLS_BASE)/docs.mk

install: all
	${INSTALL} -m 755 -d ${DOCDIR}/sid/${NAME}-single
	${INSTALL} -m 644 ../xhtml/${NAME}-single/* ${DOCDIR}/sid/${NAME}-single/
	${INSTALL} -m 755 -d ${DOCDIR}/sid/${NAME}
	${INSTALL} -m 644 ../xhtml/${NAME}/* ${DOCDIR}/sid/${NAME}/

