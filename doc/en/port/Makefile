# $TenDRA$

.if exists(../Makefile.inc)
.include "../Makefile.inc"
.endif

.PATH :	${.CURDIR}/images ${.CURDIR}/../images

IMAGES_OBJ?=	tdf_link.obj token.obj token_args.obj eg_scheme.obj

# shared images.
IMAGES_OBJ+=	trad_scheme.obj tdf_scheme.obj

DOC?= book

SRCS=   book.sgml

.include "${DOC_PREFIX}/share/mk/doc.project.mk"
