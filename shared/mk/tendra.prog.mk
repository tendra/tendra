# TenDRA make build infrastructure
#
# $Id$

.if !defined(_TENDRA_WORK_PROG_MK_)
_TENDRA_WORK_PROG_MK_=1

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
WRAP_BIN?=	${PREFIX}/bin

#.if !empty(LIBS)
#LDOPTS+=	-L${PREFIX}/lib
#.endif

${OBJ_SDIR}/${PROG}: ${OBJS}
	@${CONDCREATE} "${OBJ_SDIR}"
	@${ECHO} "==> Linking ${WRKDIR}/${PROG}"
	${CC} ${LDOPTS} -o ${.TARGET} ${OBJS} ${LIBS}

.if defined(WRAPPER)
${OBJ_SDIR}/${WRAPPER}: ${WRAPPER}
	@${CONDCREATE} "${OBJ_SDIR}"
	@${ECHO} "==> Setting paths for ${WRKDIR}/${WRAPPER}"
	sed -e 1,\$$s%@@MACH_BASE@@%${MACH_BASE}%g \
	    -e 1,\$$s%@@EXEC_BIN@@%${EXEC_BIN}%g   \
	    -e 1,\$$s%@@PREFIX@@%${PREFIX}%g       \
	    ${WRAPPER} > ${.TARGET}
.endif



#
# User-facing targets
#

all:: ${OBJ_SDIR}/${PROG}
.if defined(WRAPPER)
all:: ${OBJ_SDIR}/${WRAPPER}
.endif


clean::
	${REMOVE} ${OBJ_SDIR}/${PROG} ${PROG}.core core
.if defined(WRAPPER)
	${REMOVE} ${OBJ_SDIR}/${WRAPPER}
.endif


install:: all
	@${CONDCREATE} "${EXEC_BIN}"
.if defined(WRAPPER)
	@${CONDCREATE} "${WRAP_BIN}"
.endif
	@${ECHO} "==> Installing ${WRKDIR}/${PROG}"
	${INSTALL} -m 755 ${OBJ_SDIR}/${PROG} ${EXEC_BIN}/${PROG}
.if defined(WRAPPER)
	${INSTALL} -m 755 ${OBJ_SDIR}/${WRAPPER} ${WRAP_BIN}/${PROG}
.endif



.endif	# !defined(_TENDRA_WORK_PROG_MK_)
