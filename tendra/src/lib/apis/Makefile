# $TenDRA$
# If your working on a tspec file, and only want it to check the specific
# directory you are working on, invoke make like:
#
# APIS="ansi iso" make
#

# Directories where the api library makefiles are. (respectivly)
SUBDIR=	ansi bsd_extn cpp gcc posix1 posix2 svid3 unix95 xpg4 diag

#These are broken and need to be checked
#SUBDIR+= posix xpg3


APIS?=	ansi iso cpp posix posix1 posix2 \
	xpg3 xpg4 svid3 unix95 motif/1_2 gcc bsd_extn \
	x5/lib x5/t x5/aw x5/mu x5/proto x5/ext x5/mit

DEPEND_SRC=	${APIS}

# tspec (thankfully) can do it's own timestamping of files to decide what needs
# to be updated or not.
${APIS}:
	${TSPEC} -w -v -O${OBJ_DIR} -S${OBJ_DIR} -I${.CURDIR} ${.TARGET}

all: obj-dir
.for entry in ${SUBDIR}
	@${ECHO} "===> ${DIRPRFX}${entry}"
	@${ECHO} "===> ${entry}# ${MAKE} make-subdir"
	@cd ${.CURDIR}/${entry}; \
		${MAKE} make-subdir
.endfor

.include "../../../mk/base/tendra.prog.mk"
