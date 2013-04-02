# $Id$

.include "Makefile.inc"

.include <tendra.base.mk>


${OBJ_SDIR}/${.CURDIR:T}.xml: 
	@${CONDCREATE} "${OBJ_SDIR}"

${OBJ_DDIR}/${trans}.1/${DOC_INDEX}: ${OBJ_SDIR}/${trans}.1.xml
	${MAKE} -DMAN=${trans}.1 -DDOC_SRC=${OBJ_SDIR}/${trans}.1.xml -DSUBDOC ${.TARGET}

x:: ${OBJ_DDIR}/${trans}.1/${DOC_INDEX}


curdir!=	pwd
MAN=	${curdir:T}


.include <tendra.doc.mk>


TRANS+=	trans-all.1
TRANS+=	trans386.1
TRANS+=	alphatrans.1
TRANS+=	hppatrans.1
TRANS+=	mipstrans.1
TRANS+=	powertrans.1
TRANS+=	sparctrans.1

# XXX: hacky
regen::
.for trans in ${TRANS}
	@${ECHO} "==> Transforming ${WRKDIR}/${trans}.xml"
	${XSLTPROC} ${XMLOPTS} ${XSLTOPTS} -o ${trans}.xml \
		--stringparam trans ${trans:R:C/^trans-all$/all/} trans-xsl.1.xsl trans-xsl.1.xsl
.endfor

