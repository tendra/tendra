# $TenDRA$

.PATH :	${.CURDIR}/images ${.CURDIR}/../images

PDF_TITLE=	TDF Portability Guide
PDF_SUBJECT=	TDF Portability Guide

IMAGES_OBJ?=	tdf_link.obj token.obj token_args.obj eg_scheme.obj

# shared images.
IMAGES_OBJ+=	trad_scheme.obj tdf_scheme.obj

DOC?= book

SRCS=   book.sgml

.include "../Makefile.inc"
.include "${DOC_PREFIX}/share/mk/doc.project.mk"
