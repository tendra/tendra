# $Id$

TIDY= tidy
XMLLINT= xmllint
XSLTPROC= xsltproc

TIDYFLAGS= --doctype strict\
	   --output-xhtml yes\
	   -im -wrap 78 -utf8

XMLLINTFLAGS= --noout --valid

# Typical BSD and pkgsrc locations.
PREFIX=	/usr/local/share /usr/pkg/share
.for prefix in ${PREFIX}
. if exists(${prefix}/xsl/docbook/xhtml/docbook.xsl)
DBXSL=	${prefix}/xsl/docbook/xhtml/docbook.xsl
. endif
.endfor

${DOC}.html: ${DOC}.xml
	${XSLTPROC} -o ${.TARGET} ${DBXSL} ${DOC}.xml
	${TIDY} ${TIDYFLAGS} ${.TARGET}

all: ${DOC}.html

clean:
	rm -f ${DOC}.html

lint: ${DOC}.xml
	${XMLLINT} ${XMLLINTFLAGS} ${DOC}.xml
