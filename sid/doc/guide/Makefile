# $Id$
# TODO: perhaps an extra-params variable, for:
#    <xsl:param name="css.decoration">0</xsl:param>
#    <xsl:param name="paper.type">A4</xsl:param>
#    <xsl:param name="section.autolabel">1</xsl:param>
#    <xsl:param name="section.label.includes.component.label">1</xsl:param>


NAME=guide
SOURCE=guide.xml
PROJECT_NAME=sid
PROJECT_URL=http://docs.tendra.org/
RESOURCES=../style/docbook.css ../style/common.css
CSSFILE=docbook.css
XHTMLSTYLE=../xsl/tendra-docbook-chunked.xsl
XHTMLSTYLE_SINGLE=../xsl/tendra-docbook-single.xsl

PREFIX?=/usr/local
SHAREDIR?=${PREFIX}/share
DOCDIR?=${SHAREDIR}/doc

include ../doctools/Mk/docbook.mk

install: all
	install -m 755 -d ${DOCDIR}/sid/$(NAME)-single
	install -m 644 ../xhtml/$(NAME)-single/* ${DOCDIR}/sid/$(NAME)-single/
	install -m 755 -d ${DOCDIR}/sid/$(NAME)
	install -m 644 ../xhtml/$(NAME)/* ${DOCDIR}/sid/$(NAME)/

