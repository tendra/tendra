# $Id$

TIDY= tidy
XSLTPROC= xsltproc

DBSRCS=	calculus/calculus.xml diagnostic/diagnostic.xml tcpplus/tcpplus.xml\
	tspec/tspec.xml

# Typical BSD and pkgsrc locations.
PREFIX=	/usr/local/share /usr/pkg/share
.for prefix in ${PREFIX}
. if exists(${prefix}/xsl/docbook/xhtml/docbook.xsl)
DBXSL=	${prefix}/xsl/docbook/xhtml/docbook.xsl
. endif
.endfor

all:
.for i in ${DBSRCS}
	${XSLTPROC} -o ${i:C/xml/html/} --xinclude ${DBXSL} ${i}
	${TIDY} -im -wrap 78 -access 1 -utf8 ${i:C/xml/html/}
.endfor

clean:
.for i in ${DBSRCS}
. if exists(${i:C/xml/html/})
	rm ${i:C/xml/html/}
. endif
.endfor
