# $TenDRA$

.if exists(../Makefile.inc)
.include "../Makefile.inc"
.endif

DOC?=	article

SRCS=	article.sgml

article.html article.pdf: individual.sgml organisation.sgml

individual.sgml: individual
	${CAT} ${.CURDIR}/individual \
		|sort \
		|awk -f ${.CURDIR}/individual.awk \
		> ${.CURDIR}/individual.sgml

organisation.sgml: organisation
	${CAT} ${.CURDIR}/organisation \
		|sort \
		|awk -f ${.CURDIR}/organisation.awk \
		> ${.CURDIR}/organisation.sgml


CLEANFILES=	individual.sgml organisation.sgml

.include "${DOC_PREFIX}/share/mk/doc.project.mk"
