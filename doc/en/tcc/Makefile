# $TenDRA$

.if exists(../Makefile.inc)
.include "../Makefile.inc"
.endif

.PATH :	${.CURDIR}/images ${.CURDIR}/../images

IMAGES_OBJ?=	mips_files.obj tcc_files.obj tcc_scheme.obj

# shared images.
IMAGES_OBJ+=	trad_scheme.obj tdf_scheme.obj

DOC?= book

SRCS=   book.sgml

.include "${DOC_PREFIX}/share/mk/doc.project.mk"
