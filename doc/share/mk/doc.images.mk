#
# $TenDRA$
#

PNMTOPNG?=	pnmtopng
XPMTOPPM?=	xpmtoppm
TGIF?=		tgif


IMAGES_PNG=	${IMAGES_OBJ:R:S/$/.png/g}
IMAGES_EPS=	${IMAGES_OBJ:R:S/$/.eps/g}

LOCAL_IMAGES_PNG=	${IMAGES_PNG}
LOCAL_IMAGES_EPS=	${IMAGES_EPS}


# Use suffix rules to convert .scr files to .png files
.SUFFIXES:	.png .eps .obj

.obj.eps:
	${TGIF} -print -eps -stdout ${.IMPSRC} > ${.CURDIR}/${.TARGET}

.obj.png:
	${TGIF} -print -xpm -stdout ${.IMPSRC} |\
		${XPMTOPPM} |\
		${PNMTOPNG} > ${.CURDIR}/${.TARGET}
