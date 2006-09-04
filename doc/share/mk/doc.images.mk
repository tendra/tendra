#
# $TenDRA: doc.images.mk 2447 2006-03-23 21:15:51Z verm $
#

PNMTOPNG?=	pnmtopng
XPMTOPPM?=	xpmtoppm
TGIF?=		tgif
RSVG?=		rsvg

IMAGES_PNG=	${IMAGES_OBJ:R:S/$/.png/g}
IMAGES_EPS=	${IMAGES_OBJ:R:S/$/.eps/g}

LOCAL_IMAGES_PNG=	${IMAGES_PNG}
LOCAL_IMAGES_EPS=	${IMAGES_EPS}

# Use suffix rules to convert .scr files to .png files
.SUFFIXES:	.png .eps .obj .svg

.obj.eps:
	${TGIF} -print -eps -stdout ${.IMPSRC} > ${.CURDIR}/${.TARGET}

.obj.png:
	${TGIF} -print -xpm -stdout ${.IMPSRC} |\
		${XPMTOPPM} |\
		${PNMTOPNG} > ${.CURDIR}/${.TARGET}

.svg.png:
	${RSVG} ${.IMPSRC} ${.TARGET}
