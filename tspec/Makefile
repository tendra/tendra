# $Id$

.include "Makefile.inc"


${OBJ_DIR}/src/tspec:
	cd ${src} && ${MAKE} ${.TARGET}


.if !exists(Makefile.defs)
.BEGIN:
	@${ECHO} "Please run 'makedefs' prior to running (b)make"
	@${ECHO}
	@${EXIT} 1;
.endif


SUBDIR+=	src
SUBDIR+=	doc

.include <tendra.subdir.mk>


TSPEC=	${OBJ_DIR}/src/tspec
TSPEC_FLAGS+=	-a

BASE_APIS+=	ansi
BASE_APIS+=	iso
BASE_APIS+=	posix
BASE_APIS+=	posix1
BASE_APIS+=	posix2
#BASE_APIS+=	posix3
BASE_APIS+=	unix95
BASE_APIS+=	xpg3
BASE_APIS+=	xpg4
BASE_APIS+=	svid3
BASE_APIS+=	svid3

EXT_APIS+=	bsd_extn
EXT_APIS+=	dummy
EXT_APIS+=	gcc
EXT_APIS+=	cpp
EXT_APIS+=	motif/1_2
EXT_APIS+=	x5/aw
EXT_APIS+=	x5
EXT_APIS+=	x5/lib
EXT_APIS+=	x5/mit
EXT_APIS+=	x5/mu
EXT_APIS+=	x5/proto
EXT_APIS+=	x5/t

.include <tendra.tspec.mk>

