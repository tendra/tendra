# $TenDRA$

.PATH :	${.CURDIR}/images ${.CURDIR}/../images

PDF_TITLE=	tcc User's Guide
PDF_SUBJECT=	tcc User's Guide

IMAGES_OBJ?=	mips_files.obj tcc_files.obj tcc_scheme.obj

# shared images.
IMAGES_OBJ+=	trad_scheme.obj tdf_scheme.obj

DOC?= book

SRCS=   book.sgml

.include "../Makefile.inc"
.include "${DOC_PREFIX}/share/mk/doc.project.mk"
