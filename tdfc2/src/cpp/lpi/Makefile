# $Id$

.include "Makefile.inc"

.include <tendra.base.mk>
.include <tendra.functions.mk>


# TODO: figure out where to install LPI token libraries.
# Maybe install as ${PREFIX_LPI}/cpp.tl


SYS_FILES+=	basic.j
SYS_FILES+=	throw.j
SYS_FILES+=	ptr_func.j
SYS_FILES+=	ptr_mem.j
SYS_FILES+=	vtable.j

SYS_FILES:=	${SYS_FILES:C,^,${OBJ_SDIR}/,g}


# Here we're using tcc(1) to call the not-yet-installed C++ producer.
# This way, we can make use of tcc's usual environments, which is far more
# convenient than explicitly specifying everything (like error-checking
# profiles) to the C++ producer by hand.

TXXOPTS+=	-I${.CURDIR:H}/stdlib

# Tell tcc(1) where to find our pre-'make install' C++ producer binary
TXXOPTS+=	-Ex:${OBJ_SDIR:H}/tcpplus

# Tell the -Yc++ environment where to find the C++ tspec API
TXXOPTS+=	-yTENDRA_INCLDIR=${PREFIX_TSPEC}/TenDRA/include

${OBJ_SDIR}/basic.j: basic.cc
	@${CONDCREATE} "${OBJ_SDIR}"
	@${ECHO} "==> Compiling ${WRKDIR}/${.ALLSRC:T}"
	${TCC} ${TCCOPTS} -Yc++ ${TXXOPTS} -Fj -o ${.TARGET} ${.ALLSRC}

${OBJ_SDIR}/throw.j: throw.cc
	@${CONDCREATE} "${OBJ_SDIR}"
	@${ECHO} "==> Compiling ${WRKDIR}/${.ALLSRC:T}"
	${TCC} ${TCCOPTS} -Yc++ ${TXXOPTS} -Fj -o ${.TARGET} ${.ALLSRC}


${OBJ_SDIR}/ptr_func.j: ptr_func.p
	@${CONDCREATE} "${OBJ_SDIR}"
	@${ECHO} "==> Translating ${WRKDIR}/${.ALLSRC:T}"
	${TCC} ${TCCOPTS} -Ytnc ${TNCOPTS} -Fj -o ${.TARGET} ${.ALLSRC}

${OBJ_SDIR}/ptr_mem.j: ptr_mem.p
	@${CONDCREATE} "${OBJ_SDIR}"
	@${ECHO} "==> Translating ${WRKDIR}/${.ALLSRC:T}"
	${TCC} ${TCCOPTS} -Ytnc ${TNCOPTS} -Fj -o ${.TARGET} ${.ALLSRC}

${OBJ_SDIR}/vtable.j: vtable.p
	@${CONDCREATE} "${OBJ_SDIR}"
	@${ECHO} "==> Translating ${WRKDIR}/${.ALLSRC:T}"
	${TCC} ${TCCOPTS} -Ytnc ${TNCOPTS} -Fj -o ${.TARGET} ${.ALLSRC}


# TODO: for some reason I can't get tcc -Ymakelib to call tld -mc here, so I am
# simply calling it directly. I'd rather use tcc, because then we can elide the
# dependency on passing in the ${TLD} variable from the user's perspective.
${OBJ_SDIR}/cpp.tl: ${SYS_FILES}
	@${CONDCREATE} "${OBJ_SDIR}"
	@${ECHO} "==> Linking ${WRKDIR}/${.ALLSRC:T}"
	${TLD} -mc -o ${.TARGET} ${.ALLSRC}


all:: ${OBJ_SDIR}/cpp.tl

clean::
	${RMFILE} ${SYS_FILES} ${OBJ_SDIR}/cpp.tl

install::


