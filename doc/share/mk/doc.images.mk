#
# $TenDRA$
#

SCR2PNG?=	${PREFIX}/bin/scr2png
SCR2PNGOPTS?=	${SCR2PNGFLAGS}

EPS2PNG?=	${PREFIX}/bin/peps
EPS2PNGOPTS?=	-p -r ${EPS2PNG_RES} ${EPS2PNGFLAGS}

PNGTOPNM?=	${PREFIX}/bin/pngtopnm
PNGTOPNMOPTS?=	${PNGTOPNMFLAGS}

PNMTOPS?=	${PREFIX}/bin/pnmtops
PNMTOPSOPTS?=	-noturn ${PNMTOPSFLAGS}

EPSTOPDF?=	${PREFIX}/bin/epstopdf
EPSTOPDFOPTS?=	${EPSTOPDFFLAGS}

PS2EPS?=	${PREFIX}/bin/ps2epsi
PIC2PS?=	${GROFF} -p -S -Wall -mtty-char -man 
TGIF?=		/usr/X11R6/bin/tgif

LOCAL_IMAGES_LIB=	

IMAGES_PNG=	${IMAGES_OBJ:R:S/$/.png/g}
IMAGES_EPS=	${IMAGES_OBJ:R:S/$/.eps/g}
IMAGES_PDF=	${IMAGES_OBJ:R:S/$/.pdf/g}

LOCAL_IMAGES_PNG=	${IMAGES_PNG}
LOCAL_IMAGES_EPS=	${IMAGES_EPS}
LOCAL_IMAGES_PDF=	${IMAGES_PDF}


# Use suffix rules to convert .scr files to .png files
.SUFFIXES:	.png .eps .obj .pdf

.obj.eps:
	@echo EPS

.obj.png:
	${TGIF} -print -xpm -stdout ${.IMPSRC} |\
		xpmtoppm |\
		ppmchange white rgb:EE/EE/EE |\
		pnmtopng > ${.TARGET}

.obj.pdf:
	${TGIF} -print -eps -stdout ${.IMPSRC} |\
		${EPSTOPDF} -f --outfile=${.TARGET}

