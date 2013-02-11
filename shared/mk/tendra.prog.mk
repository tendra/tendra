# $Id$

# Copyright 2004-2011, The TenDRA Project.
#
# See doc/copyright/ for the full copyright terms.


.if !defined(_TENDRA_PROG_MK_)
_TENDRA_PROG_MK_=1

.include <tendra.base.mk>
.include <tendra.functions.mk>
.include <tendra.compiler.mk>

.if !defined(OBJS)
.BEGIN:
	@${ECHO} '$${OBJS} must be set'
	@${EXIT} 1;
.endif

.if !defined(PROG)
.BEGIN:
	@${ECHO} '$${PROG} must be set'
	@${EXIT} 1;
.endif



EXEC_BIN?=	${PREFIX}/bin

#.if !empty(LIBS)
#LDOPTS+=	-L${PREFIX}/lib
#.endif

${OBJ_SDIR}/${PROG}: ${OBJS}
	@${CONDCREATE} "${OBJ_SDIR}"
	@${ECHO} "==> Linking ${WRKDIR}/${PROG}"
	${CC} ${LDOPTS} -o ${.TARGET} ${OBJS} ${LIBS}



#
# User-facing targets
#

all:: ${OBJ_SDIR}/${PROG}


clean::
	${RMFILE} ${OBJ_SDIR}/${PROG} ${PROG}.core core


install:: all
	@${CONDCREATE} "${EXEC_BIN}"
	@${ECHO} "==> Installing ${WRKDIR}/${PROG}"
	${INSTALL} -m 755 ${OBJ_SDIR}/${PROG} ${EXEC_BIN}/${PROG}



.endif
